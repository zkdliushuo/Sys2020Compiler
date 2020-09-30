#include "assembly_builder.h"
#include <vector>

using namespace YAL;
using namespace c1_recognizer::syntax_tree;

void PutTypeName(Type* type, LLVMContext &context){
    auto Int32Ty = Type::getInt32Ty(context);
    auto Int32Pty = Type::getInt32PtrTy(context);
    auto Int1Ty = Type::getInt1Ty(context);
    if(type->isPointerTy()){
        // if(type->getPointerElementType()->getTypeID() == Int32Ty->getTypeID()){
        //     std::cout << "Stors Unit of Int 32 Type"<<std::endl;
        // }
        if (type->getPointerElementType()->getTypeID() == Int32Pty->getTypeID()){
            std::cout << "Pointer to Int 32 Pointer Type"<<std::endl;
        }
        else if (type->getTypeID() == Int32Pty->getTypeID()){
            std::cout << "Int 32 Pointer Type"<<std::endl;
        }
        else{
            std::cout << "Undefined Type! WRONG"<<std::endl;
        }
    }
    else if(type->isIntegerTy()){
        if(type->getTypeID() == Int32Ty->getTypeID()){
            std::cout << "Int 32 Type"<<std::endl;
        }
        else if(type->getTypeID() == Int1Ty->getTypeID()){
            std::cout << "Boolean Type"<<std::endl;
        }
        else{
            std::cout << "Undefined Type! WRONG"<<std::endl;
        }
    }
    else{
        std::cout << "Undefined Type! WRONG"<<std::endl;
    }
}

// 传参数时数组可以支持子数组索引
std::vector<int> assembly_builder::CalCurIndex()
{
    std::vector<int> CurIndex;
    int size = ConstArrayInitVec.size();
    std::vector<int>::reverse_iterator iter = ArrayLength.rbegin();
    for (; iter != ArrayLength.rend(); ++iter){
        CurIndex.insert(CurIndex.begin(), size %  (*iter));
        size=size/(*iter);
    }
    return CurIndex;
}

auto get_int_const(LLVMContext &context, int number) 
{
    return ConstantInt::get(context, number, 32);
}

void assembly_builder::visit(assembly &node)
{
    // PrintSymbolTable();
    error_flag = false;
    auto children = node.global_defs;
    bb_count = 0;
    constexpr_expected = false;
    in_funcRParam = false;
    lval_as_rval = true;
    for(auto &child : children)
    {
        in_global =true;
        child->accept(*this);
    }
}

void assembly_builder::visit(init_const_syntax &node)
{
    constexpr_expected = true;
    if(ArrayLength.empty()){
        if(node.single_init==nullptr){
            error_flag = true;
            err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                        "Not an array type, should not be initilized as array type.");
            return;
        }
        else{
            node.single_init->accept(*this);
            ConstArrayInitVec.push_back(int_const_result);
            return;
        }
    }
    else{
        // 处理出错
        if(array_init_depth>ArrayLength.size()){
            error_flag = true;
            err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                        "Too many array initializers.");
            return;
        }

        if(node.single_init){
            // std::cout<<"Turns out that extra single_init is still working although I think it's rebundant!"<<std::endl;
            node.single_init->accept(*this);
            ConstArrayInitVec.push_back(int_const_result);
            return;
        }
        for(auto each: node.array_init){
            if(each->single_init){
                each->single_init->accept(*this);
                ConstArrayInitVec.push_back(int_const_result);
            }
            else{
                // 在初始化下一层之前，补0
                // auto CurIndex =  CalCurIndex();
                // if(CurIndex.at(array_init_depth-1)>=ArrayLength.at(array_init_depth-1)){
                //     error_flag = true;
                //     err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                //                 "Too many initializers before the last Array Initialization.");
                //     return;
                // }
                int divident = 1,PushZeros;
                for(int i=array_init_depth;i<ArrayLength.size();i++){
                    divident*=ArrayLength.at(i);
                }
                if(ConstArrayInitVec.size() % divident != 0){
                    PushZeros = (ConstArrayInitVec.size() / divident + 1)*divident - ConstArrayInitVec.size();
                    while (PushZeros--){
                        ConstArrayInitVec.push_back(0);
                    }
                }
                assert(ConstArrayInitVec.size() % divident == 0);

                // 初始化下一层
                int expected_size = ConstArrayInitVec.size() + divident;
                array_init_depth++;
                each->accept(*this);
                array_init_depth--;

                // 初始化下一层之后，补0
                PushZeros = expected_size - ConstArrayInitVec.size(); 
                while (PushZeros--){
                    ConstArrayInitVec.push_back(0);
                }
            }
        }
    }
}

void assembly_builder::visit(const_def_stmt_syntax &node)
{
    assert(node.initializers);
    ArrayLength.clear();
    Value *current_var;
    if(in_global){
        // 非数组变量
        if(node.array_length.empty()){
            ConstArrayInitVec.clear();
            if(node.initializers->single_init==nullptr){
                error_flag = true;
                err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                        "Variable's initialization should not be treated as Array type.");
                return;
            }
            node.initializers->accept(*this);
            current_var = new GlobalVariable(
                    *module.get(),
                    Type::getInt32Ty(context),
                    true, // 是整数
                    get_int_const(context, ConstArrayInitVec.front()),
                    node.name
            );
        }
        else
        {
            // global array type
            // 计算所有维度的const expression
            for(auto each : node.array_length){
                each->accept(*this);
                if (int_const_result < 0) 
                {
                    error_flag = true;
                    err.error(static_cast<size_t>(each->line), static_cast<size_t>(each->pos),
                            "array length should be greater or equal to zero.");
                    return;
                }
                ArrayLength.push_back(int_const_result);
            }

            // 把数组拍扁，因此这里是把所有维的长度相乘作为一个一维数组的长度
            int length=1;
            for(auto each: ArrayLength){
                length*=each;
            }
            auto array_variable_type =  ArrayType::get(Type::getInt32Ty(context), static_cast<uint64_t>(length)) ;

            // 按照前面计算的数组长度，下面计算所有的初始化值，下面的计算依赖于数组长度和数组维度的计算
            if(node.initializers==nullptr){
                error_flag = true;
                err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                        "Const should be initialized at the very beginning.");
                return;
            }
            array_init_depth = 1;
            ConstArrayInitVec.clear();
            if(node.initializers->single_init){
                error_flag = true;
                err.error(static_cast<size_t>(node.initializers->line), static_cast<size_t>(node.initializers->pos),
                        "Array type should be initialized by a const expression.");
                return;
            }
            node.initializers->accept(*this);
            if(ConstArrayInitVec.size()>length){
                error_flag = true;
                err.error(static_cast<size_t>(node.initializers->line), static_cast<size_t>(node.initializers->pos),
                        "More initializers than expected.");
                return;
            }
            else{
                auto PushZeros = length - ConstArrayInitVec.size();
                while (PushZeros--){
                    ConstArrayInitVec.push_back(0);
                }
            }
            std::vector<Constant *> init_values;
            for(auto each : ConstArrayInitVec){
                init_values.push_back(get_int_const(context,each));
            }
            auto initialized_array = ConstantArray::get(array_variable_type, init_values);

            // 声明全局变量
            current_var = new GlobalVariable(
                    *module.get(),
                    array_variable_type,
                    true,
                    initialized_array,
                    node.name
            );
        }
    }
    else
    {
        // 局部非数组变量
        if (node.array_length.empty()) 
        {
            // 声明allocation
            auto variable_type = Type::getInt32Ty(context);
            current_var = builder.CreateAlloca(variable_type, nullptr, node.name);
            ConstArrayInitVec.clear();
            if(node.initializers->single_init==nullptr){
                error_flag = true;
                err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                        "Variable's initialization should not be treated as Array type.");
                return;
            }
            node.initializers->accept(*this);
            builder.CreateStore(get_int_const(context, ConstArrayInitVec.front()), current_var);
        } 
        else 
        {
            for(auto each : node.array_length){
                each->accept(*this);
                if (int_const_result < 0) 
                {
                    error_flag = true;
                    err.error(static_cast<size_t>(each->line), static_cast<size_t>(each->pos),
                            "array length should be greater or equal to zero.");
                    return;
                }
                ArrayLength.push_back(int_const_result);
            }

            // 把数组拍扁，因此这里是把所有维的长度相乘作为一个一维数组的长度
            int length=1;
            for(auto each: ArrayLength){
                length*=each;
            }
            auto array_variable_type =  ArrayType::get(Type::getInt32Ty(context), static_cast<uint64_t>(length)) ;

            // 按照前面计算的数组长度，下面计算所有的初始化值，下面的计算依赖于数组长度和数组维度的计算
            if(node.initializers==nullptr){
                error_flag = true;
                err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                        "Const should be initialized at the very beginning.");
                return;
            }
            array_init_depth = 1;
            ConstArrayInitVec.clear();
            if(node.initializers->single_init){
                error_flag = true;
                err.error(static_cast<size_t>(node.initializers->line), static_cast<size_t>(node.initializers->pos),
                        "Array type should be initialized by a const expression.");
                return;
            }
            node.initializers->accept(*this);
            if(ConstArrayInitVec.size()>length){
                error_flag = true;
                err.error(static_cast<size_t>(node.initializers->line), static_cast<size_t>(node.initializers->pos),
                        "More initializers than expected.");
                return;
            }
            else{
                auto PushZeros = length - ConstArrayInitVec.size();
                while (PushZeros--){
                    ConstArrayInitVec.push_back(0);
                }
            }
            std::vector<Constant *> init_values;
            for(auto each : ConstArrayInitVec){
                init_values.push_back(get_int_const(context,each));
            }
            auto initialized_array = ConstantArray::get(array_variable_type, init_values);
            current_var = builder.CreateAlloca(array_variable_type, get_int_const(context, length), node.name);
            int i=0;
            for (auto &current_init_value : ConstArrayInitVec) 
            {
                ArrayRef<Value*> index_list = {get_int_const(context, 0), get_int_const(context, i++)};
                auto index = builder.CreateInBoundsGEP(current_var, index_list);
                builder.CreateStore(get_int_const(context, current_init_value), index);
            }
        }
    }

    auto flag = declare_variable(
            node.name,
            current_var,
            true,
            !node.array_length.empty()
    );
    if (not flag) {
        // name already exists
        error_flag = true;
        err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                  "duplicated declaration " + node.name + " .");
        return;
    }
    if(!ArrayLength.empty()){
        // std::vector<Value*> DynamicIndex;
        // for(auto each: ArrayLength){
        //     DynamicIndex.push_back(get_int_const(context,each));
        // }
        if(!SetArraySize(node.name, ArrayLength)){
            error_flag = true;
            err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                    "Double set array size Or Set array size to a non array type" + node.name + " .");
            return;
        }
    }
    if(!SetConstInit(node.name,ConstArrayInitVec)){
        error_flag = true;
        err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                  "Store Initial value fails " + node.name + " .");
        // PrintSymbolTable();
        return;
    }
}

void assembly_builder::visit(init_var_syntax &node)
{
    if(in_global){
        // 在global作用域下，所有的初始化表达式都是常量表达式
        constexpr_expected = true;
        if(ArrayLength.empty()){
            if(node.single_init==nullptr){
                error_flag = true;
                err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                            "Not an array type, should not be initilized as array type.");
                return;
            }
            else{
                node.single_init->accept(*this);
                ConstArrayInitVec.push_back(int_const_result);
                return;
            }
        }
        else{
            // 处理出错
            if(array_init_depth>ArrayLength.size()){
                error_flag = true;
                err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                            "Too many array initializers.");
                return;
            }

            if(node.single_init){
                // std::cout<<"Turns out that extra single_init is still working although I think it's rebundant!"<<std::endl;
                node.single_init->accept(*this);
                ConstArrayInitVec.push_back(int_const_result);
                return;
            }
            for(auto each: node.array_init){
                if(each->single_init){
                    each->single_init->accept(*this);
                    ConstArrayInitVec.push_back(int_const_result);
                }
                else{
                    int divident = 1,PushZeros;
                    for(int i=array_init_depth;i<ArrayLength.size();i++){
                        divident*=ArrayLength.at(i);
                    }
                    if(ConstArrayInitVec.size() % divident != 0){
                        PushZeros = (ConstArrayInitVec.size() / divident + 1)*divident - ConstArrayInitVec.size();
                        while (PushZeros--){
                            ConstArrayInitVec.push_back(0);
                        }
                    }
                    assert(ConstArrayInitVec.size() % divident == 0);

                    // 初始化下一层
                    int expected_size = ConstArrayInitVec.size() + divident;
                    array_init_depth++;
                    each->accept(*this);
                    array_init_depth--;

                    // 初始化下一层之后，补0
                    PushZeros = expected_size - ConstArrayInitVec.size(); 
                    while (PushZeros--){
                        ConstArrayInitVec.push_back(0);
                    }
                }
            }
        }
    }
    else{
        constexpr_expected = false;
        if(ArrayLength.empty()){
            if(node.single_init==nullptr){
                error_flag = true;
                err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                            "Not an array type, should not be initilized as array type.");
                return;
            }
            else{
                node.single_init->accept(*this);
                VarArrayInitVec.push_back(value_result);
                return;
            }
        }
        else{
            // 处理出错
            if(array_init_depth>ArrayLength.size()){
                error_flag = true;
                err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                            "Too many array initializers.");
                return;
            }

            if(node.single_init){
                // std::cout<<"Turns out that extra single_init is still working although I think it's rebundant!"<<std::endl;
                node.single_init->accept(*this);
                VarArrayInitVec.push_back(value_result);
                return;
            }
            for(auto each: node.array_init){
                if(each->single_init){
                    each->single_init->accept(*this);
                    VarArrayInitVec.push_back(value_result);
                }
                else{
                    int divident = 1,PushZeros;
                    for(int i=array_init_depth;i<ArrayLength.size();i++){
                        divident*=ArrayLength.at(i);
                    }
                    if(VarArrayInitVec.size() % divident != 0){
                        PushZeros = (VarArrayInitVec.size() / divident + 1)*divident - VarArrayInitVec.size();
                        while (PushZeros--){
                            VarArrayInitVec.push_back(get_int_const(context,0));
                        }
                    }
                    assert(VarArrayInitVec.size() % divident == 0);

                    // 初始化下一层
                    int expected_size = VarArrayInitVec.size() + divident;
                    array_init_depth++;
                    each->accept(*this);
                    array_init_depth--;

                    // 初始化下一层之后，补0
                    PushZeros = expected_size - VarArrayInitVec.size(); 
                    while (PushZeros--){
                        VarArrayInitVec.push_back(get_int_const(context,0));
                    }
                }
            }
        }
    }
}

void assembly_builder::visit(var_def_stmt_syntax &node)
{
    // 几乎和const_def相同，除了varinit返回值是value，以及可以没有initval
    Value *current_var;
    ArrayLength.clear();
    if(in_global){
        if(node.array_length.empty()){
            ConstArrayInitVec.clear();
            if(node.initializers){
                if(node.initializers->single_init==nullptr){
                    error_flag = true;
                    err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                            "Variable's initialization should not be treated as Array type.");
                    return;
                }
                node.initializers->accept(*this);
                current_var = new GlobalVariable(
                        *module.get(),
                        Type::getInt32Ty(context),
                        false, // 不是常量
                        get_int_const(context, ConstArrayInitVec.front()),
                        node.name
                );
            }
            else{
                current_var = new GlobalVariable(
                        *module.get(),
                        Type::getInt32Ty(context),
                        false, // 不是常量
                        get_int_const(context, 0),
                        node.name
                );
            }
        }
        else{ // 否则，array_length 不为空，因此这是全局数组变量类型
            for(auto each : node.array_length){
                each->accept(*this);
                if (int_const_result < 0) 
                {
                    error_flag = true;
                    err.error(static_cast<size_t>(each->line), static_cast<size_t>(each->pos),
                            "array length should be greater or equal to zero.");
                    return;
                }
                ArrayLength.push_back(int_const_result);
            }

            // 把数组拍扁，因此这里是把所有维的长度相乘作为一个一维数组的长度
            int length=1;
            for(auto each: ArrayLength){
                length*=each;
            }
            auto array_variable_type =  ArrayType::get(Type::getInt32Ty(context), static_cast<uint64_t>(length)) ;

            if(node.initializers==nullptr){
                std::vector<Constant *> init_values;
                for (int i = 0; i < length; i++){
                    init_values.push_back(get_int_const(context, 0));
                }
                auto initialized_array = ConstantArray::get(array_variable_type, init_values);
                current_var = new GlobalVariable(
                        *module.get(),
                        array_variable_type,
                        false,
                        initialized_array,
                        node.name
                );
                // std::cout << "Global variable type is " << current_var->getType()->getTypeName() << std::endl;
            }
            else{
                array_init_depth = 1;
                ConstArrayInitVec.clear();
                if(node.initializers->single_init){
                    error_flag = true;
                    err.error(static_cast<size_t>(node.initializers->line), static_cast<size_t>(node.initializers->pos),
                            "Array type should be initialized by a const expression.");
                    return;
                }
                // 尽管是initval，但是在global作用域下，返回值仍然放在constarrayinitvec里
                // 需要在varinit里区分是不是全局变量初始化
                node.initializers->accept(*this);
                if(ConstArrayInitVec.size()>length){
                    error_flag = true;
                    err.error(static_cast<size_t>(node.initializers->line), static_cast<size_t>(node.initializers->pos),
                            "More initializers than expected.");
                    return;
                }
                else{
                    auto PushZeros = length - ConstArrayInitVec.size();
                    while (PushZeros--){
                        ConstArrayInitVec.push_back(0);
                    }
                }
                std::vector<Constant *> init_values;
                for(auto each : ConstArrayInitVec){
                    init_values.push_back(get_int_const(context,each));
                }
                auto initialized_array = ConstantArray::get(array_variable_type, init_values);

                // 声明全局变量
                current_var = new GlobalVariable(
                        *module.get(),
                        array_variable_type,
                        false,
                        initialized_array,
                        node.name
                );
            }
        }   
    }
    else
    {
        // 局部非数组变量
        if (node.array_length.empty()) 
        {
            // 声明allocation
            auto variable_type = Type::getInt32Ty(context);
            current_var = builder.CreateAlloca(variable_type, nullptr, node.name);
            VarArrayInitVec.clear();
            if(node.initializers){
                if(node.initializers->single_init==nullptr){
                    error_flag = true;
                    err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                            "Variable's initialization should not be treated as Array type.");
                    return;
                }
                node.initializers->accept(*this);
                builder.CreateStore( VarArrayInitVec.front(), current_var);
            }
        } 
        else 
        {
            // local array type
            for(auto each : node.array_length){
                each->accept(*this);
                if (int_const_result < 0) 
                {
                    error_flag = true;
                    err.error(static_cast<size_t>(each->line), static_cast<size_t>(each->pos),
                            "array length should be greater or equal to zero.");
                    return;
                }
                ArrayLength.push_back(int_const_result);
            }

            // 把数组拍扁，因此这里是把所有维的长度相乘作为一个一维数组的长度
            int length=1;
            for(auto each: ArrayLength){
                length*=each;
            }
            auto array_variable_type =  ArrayType::get(Type::getInt32Ty(context), static_cast<uint64_t>(length)) ;
            current_var = builder.CreateAlloca(array_variable_type, get_int_const(context, length), node.name);
            // 按照前面计算的数组长度，下面计算所有的初始化值，下面的计算依赖于数组长度和数组维度的计算
            if(node.initializers==nullptr){
                ;
            }
            else{
                array_init_depth = 1;
                VarArrayInitVec.clear();
                if(node.initializers->single_init){
                    error_flag = true;
                    err.error(static_cast<size_t>(node.initializers->line), static_cast<size_t>(node.initializers->pos),
                            "Array type should be initialized by a const expression.");
                    return;
                }
                node.initializers->accept(*this);
                if(VarArrayInitVec.size()>length){
                    error_flag = true;
                    err.error(static_cast<size_t>(node.initializers->line), static_cast<size_t>(node.initializers->pos),
                            "More initializers than expected.");
                    return;
                }
                else{
                    auto PushZeros = length - VarArrayInitVec.size();
                    while (PushZeros--){
                        VarArrayInitVec.push_back(get_int_const(context, 0));
                    }
                }

                int i=0;
                for (auto &current_init_value : VarArrayInitVec) 
                {
                    ArrayRef<Value*> index_list = {get_int_const(context, 0), get_int_const(context, i++)};
                    auto index = builder.CreateInBoundsGEP(current_var, index_list);
                    builder.CreateStore( current_init_value, index);
                }   
            }
        }
    }

    auto flag = declare_variable(
            node.name,
            current_var,
            false,
            !node.array_length.empty()
    );
    if (not flag) {
        // name already exists
        error_flag = true;
        err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                  "duplicated declaration " + node.name + " .");
        return;
    }
    if(!ArrayLength.empty()){
        // std::vector<Value*> DynamicIndex;
        // for(auto each: ArrayLength){
        //     DynamicIndex.push_back(get_int_const(context,each));
        // }
        if(!SetArraySize(node.name, ArrayLength)){
            error_flag = true;
            err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                    "Double set array size Or Set array size to a non array type" + node.name + " .");
            return;
        }
    }
}

void assembly_builder::visit(func_def_syntax &node)
{
    in_global =false;
    if(functions.count(node.name))
    {
        error_flag = true;
        err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                  "duplicated function " + node.name + " definition.");
        return;
    }
    FunctionType *fun_type;
    Type *ret_type;
    std::vector<Type *> param_types;
    if (node.is_int) {
        ret_type = Type::getInt32Ty(context);
    } else {
        ret_type = Type::getVoidTy(context);
    }
    for (auto param: node.params) {
        if (param->is_Array) {
            param_types.push_back(Type::getInt32PtrTy(context));
        } else {
            param_types.push_back(Type::getInt32Ty(context));
        }
    }
    fun_type = FunctionType::get(ret_type, param_types, false);
    current_function =Function::Create(
        fun_type,
        node.name,
        module.get()
    );
    functions.emplace(node.name, current_function);
    auto enter_block = BasicBlock::Create(context, "enter_block", current_function);
    builder.SetInsertPoint(enter_block);
    enter_scope();
    std::vector<Value *> args;
    for (auto arg = current_function->Arg_begin();arg != current_function->Arg_end();arg++) {
        args.push_back((*arg));
    }
    auto arg = current_function->Arg_begin();
    for(auto each : node.params){
        if (each->is_Array) {
            // arg->setName(each->name);
            auto array_alloc = builder.CreateAlloca(Type::getInt32PtrTy(context), nullptr, each->name);
            builder.CreateStore((*arg), array_alloc);
            auto flag = declare_variable(
                    each->name,
                    array_alloc,
                    false,
                    true
            );
            if (!flag) {
                error_flag = true;
                err.error(static_cast<size_t>(each->pos), static_cast<size_t>(each->pos),
                        "duplicated declaration " + node.name + " .");
                return;
            }
            std::vector<Value*> DynamicIndex;
            DynamicIndex.push_back(get_int_const(context,0));
            for(auto each_dimension : each->len_array){
                constexpr_expected = false;
                each_dimension->accept(*this);
                DynamicIndex.push_back(value_result);
            }
            if(!SetArraySize(each->name, DynamicIndex)){
                error_flag = true;
                err.error(static_cast<size_t>(each->line), static_cast<size_t>(each->pos),
                        "Double set array size Or Set array size to a non array type" + each->name + " .");
                return;
            }
        } 
        else {
            auto alloc = builder.CreateAlloca(Type::getInt32Ty(context), nullptr, each->name);
            builder.CreateStore(((*arg)), alloc);
            auto flag = declare_variable(
                    each->name,
                    alloc,
                    false,
                    false
            );
            if (not flag) {
                error_flag = true;
                err.error(static_cast<size_t>(each->pos), static_cast<size_t>(each->pos),
                        "duplicated declaration " + each->name + " .");
                return;
            }
        }
        arg++;
    }
    // node.body->accept(*this);
    auto children = node.body->body;
    for (auto child : children) 
    {
        constexpr_expected = false;
        child->accept(*this);
    }
    // PrintSymbolTable();
    if (builder.getInsertBlock()->getTerminator() == nullptr){
        if (current_function->getReturnType() == Type::getVoidTy(context)) {
            builder.CreateRetVoid();
        } 
        else if (current_function->getReturnType() == Type::getInt32Ty(context)){
            // exit(111);
            builder.CreateRet(get_int_const(context, 0));
        }
        
        // else if (builder.getInsertBlock()->empty()) {
        //     builder.getInsertBlock()->removeFormParent();
        // }
    }
    exit_scope();
}

void assembly_builder::visit(expr_syntax &node)
{
    lval_as_rval = true;
    node.add_expr->accept(*this);
}

void assembly_builder::visit(const_expr_syntax &node)
{
    constexpr_expected = true;
    lval_as_rval = true;
    node.add_expr->accept(*this);
    constexpr_expected = false;
}

void assembly_builder::visit(addop_expr_syntax &node)
{
    if(constexpr_expected){
        // std::cout<< node.line << " : " << node.pos <<" Const expr expected"<<std::endl;
        node.add_expr->accept(*this);
        auto int_result_1 = int_const_result;
        node.mul_expr->accept(*this);
        auto int_result_2 = int_const_result;
        if(!error_flag){
            switch (node.op){
            case binop::plus :
                int_const_result = int_result_1 + int_result_2;
                break;
            case binop::minus :
                int_const_result = int_result_1 - int_result_2;
                break;
            default:
                error_flag = true;
                err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                            "No such opcode.");
                return;
                break;
            }
        }
        else{
            err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                        "caller.");
            return;
        }
    }
    else{
        node.add_expr->accept(*this);
        auto value_result_1 = value_result;
        // std::cout << "Before mulexp" <<std::endl;
        node.mul_expr->accept(*this);
        // std::cout << "After mulexp" <<std::endl;
        auto value_result_2 = value_result; 
        if(!error_flag){
            switch (node.op)
            {
            case binop::plus :
                value_result = builder.CreateAdd(value_result_1, value_result_2);
                break;
            case binop::minus:
                value_result = builder.CreateSub(value_result_1, value_result_2);
                break;
            default:
                error_flag = true;
                err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                            "No such opcode.");
                return;
                break;
            }
        }
        else{
            err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                        "caller.");
            return;
        }
    }
}

void assembly_builder::visit(mulop_expr_syntax &node)
{
    if(constexpr_expected){
        node.mul_expr->accept(*this);
        auto int_result_1 = int_const_result;
        node.unary_expr->accept(*this);
        auto int_result_2 = int_const_result;
        if(!error_flag){
            switch (node.op){
            case binop::multiply :
                int_const_result = int_result_1 * int_result_2;
                break;
            case binop::divide :
                int_const_result = int_result_1 / int_result_2;
                break;
            case binop::modulo:
                int_const_result = int_result_1 % int_result_2;
                break;
            default:
                error_flag = true;
                err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                            "No such opcode.");
                return;
                break;
            }
        }
        else{
            err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                        "caller.");
            return;
        }
    }
    else{
        node.mul_expr->accept(*this);
        auto value_result_1 = value_result;
        node.unary_expr->accept(*this);
        auto value_result_2 = value_result; 
        if(!error_flag){
            switch (node.op)
            {
            case binop::multiply :
                value_result = builder.CreateMul(value_result_1, value_result_2);
                break;
            case binop::divide:
                value_result = builder.CreateExactSDiv(value_result_1, value_result_2);
                break;
            case binop::modulo:
                value_result = builder.CreateSRem(value_result_1, value_result_2);
                break;
            default:
                error_flag = true;
                err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                            "No such opcode.");
                return;
                break;
            }
        }
        else{
            err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                        "caller.");
            return;
        }
    }
}

void assembly_builder::visit(unaryop_expr_syntax &node)
{
     if(constexpr_expected)
    {
        node.unary_expr->accept(*this);
        if(!error_flag){
                switch (node.op)
            {
            case unaryop::plus :
                // + exp单目运算的意义？
                break;
            case unaryop::minus:
                int_const_result = -int_const_result;
                break;
            case unaryop::exclamatory:
                int_const_result = !int_const_result;
                break;
            default:
                error_flag = true;
                err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                            "No such opcode.");
                return;
                break;
            }
        }
        else
        {
            error_flag = true;
             err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                        "caller.");
            return; 
        }
    }
    else
    {
        node.unary_expr->accept(*this);
        if(!error_flag){
            switch (node.op){
                case unaryop::plus :
                    // + exp单目运算的意义？
                    break;
                case unaryop::minus:
                    value_result = builder.CreateNeg(value_result);
                    break;
                case unaryop::exclamatory:
                    value_result = builder.CreateNot(value_result);
                    value_result = CastToInt32(value_result);
                    break;
                default:
                    error_flag = true;
                    err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                                "No such opcode.");
                    return;
                    break;
            }
        }
        else
        {
            error_flag = true;
             err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                        "caller.");
            return; 
        }
    }
}

void assembly_builder::visit(func_call_expr_syntax &node)
{
    // PrintSymbolTable();
    if (functions.count(node.func_name)==0) 
    {
        error_flag = true;
        err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                  "called function " + node.func_name + " does not exists.");
        return;
    }
    auto called_function = functions[node.func_name];
    ArrayRef<Value*> args;
    if(node.func_name == "starttime" || node.func_name == "stoptime"){
        args.push_back(get_int_const(called_function->getContext(), node.line));
    }
    else{
        for (auto arg: node.func_call_params) {
            in_funcRParam = true;
            arg->accept(*this);
            args.push_back(value_result);
        }
    }
    value_result = builder.CreateCall(called_function, args);
    in_funcRParam = false;
}

void assembly_builder::visit(internal_expr_syntax &node)
{
    node.internal_expr->accept(*this);
}

void assembly_builder::visit(literal_syntax &node)
{
    int_const_result = node.intConst;
    if (!constexpr_expected)
        // not constexpr, stores to value_result
        value_result = get_int_const(context, node.intConst);
}

void assembly_builder::visit(lval_syntax &node)
{
    auto referred_variable = lookup_variable(node.name);
    if(std::get<0>(referred_variable) == nullptr)// use undeclared variable
    {
        error_flag = true;
        err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                  "undeclared variable " + node.name + " used.");
        return;
    }
    // std::cout << "Here as which Value? "<< lval_as_rval <<std::endl;
    if(in_funcRParam){
        in_funcRParam = false;
        if(std::get<2>(referred_variable)){
            auto IndexVec = GetArraySize(node.name);
            int which_one = std::get<0>(IndexVec);
            if(which_one==0){
                error_flag = true;
                err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                        "No array size information.");
                // PrintSymbolTable();
                return;
            }
            auto LengthList = std::get<1>(IndexVec);
            if(which_one==2){
                auto Int_LengthList = std::get<2>(IndexVec);
                for(auto each: Int_LengthList)
                    LengthList.push_back(get_int_const(context,each));
            }
            std::vector<Value*> indexes;
            for(auto each: node.array_index){
                each->accept(*this);
                indexes.push_back(value_result);
            }
            auto StartPty = std::get<0>(referred_variable);
            // ArrayRef<Value *> t = {index};
            auto index = static_cast<Value*>(get_int_const(context, 0));
            int i=0;
            for(;i<LengthList.size()&&i<indexes.size();i++){
                index = builder.CreateMul(index,LengthList.at(i));
                index= builder.CreateAdd(index,indexes.at(i));
            }
            for(;i<LengthList.size();i++){
                index = builder.CreateMul(index,LengthList.at(i));
            }
            if(StartPty->getType()->getPointerElementType()->isPointerTy()){
                StartPty = builder.CreateLoad(Type::getInt32PtrTy(context), StartPty);
                value_result = builder.CreateInBoundsGEP(StartPty, index);
            }
            else{
                value_result = builder.CreateInBoundsGEP(StartPty, {get_int_const(context, 0), index});
            }
            if(node.array_index.size() > LengthList.size()){
                error_flag = true;
                err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                            "Index List's length is greater than array's Length List");
                return;
            }
            else if(node.array_index.size() == LengthList.size()){
                value_result = builder.CreateLoad(Type::getInt32Ty(context) ,value_result);
            }
        }
        else{
            value_result = builder.CreateLoad(Type::getInt32Ty(context),std::get<0>(referred_variable));
        }
    }
    else{
        if(lval_as_rval)// used as rval
        {
            // std::cout << "Here is const expected? "<< constexpr_expected <<std::endl;
            if(constexpr_expected ){
                if(!std::get<1>(referred_variable)){
                    error_flag = true;
                    err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                            "const identifier expected.");
                    return;
                }
                if(std::get<2>(referred_variable)){
                    auto IndexVec = GetArraySize(node.name);
                    int which_one = std::get<0>(IndexVec);
                    if(which_one==0){
                        error_flag = true;
                        err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                                "No array size information.");
                        return;
                    }
                    if(which_one==1){
                        error_flag = true;
                        err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                                "constexpr expected.");
                        return;
                    }
                    auto LengthList = std::get<2>(IndexVec);
                    std::vector<int> indexes;
                    if(node.array_index.size() < LengthList.size()){
                        error_flag = true;
                        err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                                "array index missing.");
                        return;
                    }
                    for(auto each: node.array_index){
                        each->accept(*this);
                        indexes.push_back(int_const_result);
                    }
                    int index=indexes.front();
                    int i=1;
                    for(;i<LengthList.size()&&i<indexes.size();i++){
                        index=index*LengthList.at(i)+indexes.at(i);
                    }
                    for(;i<LengthList.size();i++){
                        index=index*LengthList.at(i);
                    }
                    auto InitList = GetConstInit(node.name);
                    int_const_result = InitList.at(index);
                }
                else{
                    int_const_result = GetConstInit(node.name).front();
                }
            }
            else{
                if(std::get<2>(referred_variable)){
                    auto IndexVec = GetArraySize(node.name);
                    int which_one = std::get<0>(IndexVec);
                    if(which_one==0){
                        error_flag = true;
                        err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                                "No array size information.");
                        // PrintSymbolTable();
                        return;
                    }
                    auto LengthList = std::get<1>(IndexVec);
                    if(which_one==2){
                        auto Int_LengthList = std::get<2>(IndexVec);
                        for(auto each: Int_LengthList)
                            LengthList.push_back(get_int_const(context,each));
                    }
                    std::vector<Value*> indexes;
                    if(node.array_index.size() < LengthList.size()){
                        error_flag = true;
                        err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                                "array index missing.");
                        return;
                    }
                    for(auto each: node.array_index){
                        each->accept(*this);
                        indexes.push_back(value_result);
                    }
                    auto index=indexes.front();
                    int i=1;
                    for(;i<LengthList.size()&&i<indexes.size();i++){
                        index = builder.CreateMul(index,LengthList.at(i));
                        index= builder.CreateAdd(index,indexes.at(i));
                    }
                    for(;i<LengthList.size();i++){
                        index = builder.CreateMul(index,LengthList.at(i));
                    }
                    auto StartPty = std::get<0>(referred_variable);
                    // PutTypeName(index->getType(), context);
                    // PutTypeName(StartPty->getType(), context);
                    // PrintSymbolTable();
                    // std::cout << "Before gep in an array" << std::endl;
                    assert(StartPty->getType() && "StartPty's Type is NULLPTR");
                    if(StartPty->getType()->getPointerElementType()->isPointerTy()){
                        // std::cout << "Is a transferred array" << std::endl;
                        StartPty = builder.CreateLoad(Type::getInt32PtrTy(context), StartPty);
                        // ArrayRef<Value *> t = {index};
                        auto GEP_result = builder.CreateInBoundsGEP(StartPty,index);
                        value_result = builder.CreateLoad(Type::getInt32Ty(context),GEP_result);
                    }
                    else{
                        // std::cout << "Is a local array" << std::endl;
                        auto GEP_result = builder.CreateInBoundsGEP(StartPty,{get_int_const(context, 0), index});
                        value_result = builder.CreateLoad(Type::getInt32Ty(context),GEP_result);
                    }
                    
                    // PutTypeName(StartPty->getType(), context);
                }
                else{
                    value_result = builder.CreateLoad(Type::getInt32Ty(context),std::get<0>(referred_variable));
                }
            }
        }
        else
        {
            if(std::get<1>(referred_variable))
            {
                error_flag = true;
                err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                        "const cannot be used as lval.");
                return;
            }
            if(!std::get<2>(referred_variable))
            {
                value_result = std::get<0>(referred_variable);
            }
            else
            {
                auto IndexVec = GetArraySize(node.name);
                int which_one = std::get<0>(IndexVec);
                if(which_one==0){
                    error_flag = true;
                    err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                            "No array size information.");
                    return;
                }
                auto LengthList = std::get<1>(IndexVec);
                if(which_one==2){
                    auto Int_LengthList = std::get<2>(IndexVec);
                    for(auto each: Int_LengthList)
                        LengthList.push_back(get_int_const(context,each));
                }
                std::vector<Value*> indexes;
                if(node.array_index.size() < LengthList.size()){
                    error_flag = true;
                    err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                            "array index missing.");
                    return;
                }
                for(auto each: node.array_index){
                    each->accept(*this);
                    indexes.push_back(value_result);
                }
                auto index=indexes.front();
                int i=1;
                for(;i<LengthList.size()&&i<indexes.size();i++){
                    index = builder.CreateMul(index,LengthList.at(i));
                    index= builder.CreateAdd(index,indexes.at(i));
                }
                for(;i<LengthList.size();i++){
                    index = builder.CreateMul(index,LengthList.at(i));
                }
                auto StartPty = std::get<0>(referred_variable);
                if(StartPty->getType()->getPointerElementType()->isPointerTy()){
                    StartPty = builder.CreateLoad(Type::getInt32PtrTy(context), StartPty);
                    // ArrayRef<Value *> t = {index};
                    value_result = builder.CreateInBoundsGEP(StartPty,index);
                }
                else{
                    value_result = builder.CreateInBoundsGEP(StartPty,{get_int_const(context, 0), index});
                }
            }
        }    
    }
}

void assembly_builder::visit(lorop_expr_syntax &node)
{
    // exit(100);
    auto temp_cond_else_bb = cond_else_bb;
    auto next_or_bb = BasicBlock::Create(context, "next_or_bb" + std::to_string(bb_count++), current_function);
    cond_else_bb = next_or_bb;
    node.lor_expr->accept(*this);
    builder.SetInsertPoint(next_or_bb);
    cond_else_bb = temp_cond_else_bb;
    node.land_expr->accept(*this);
}

void assembly_builder::visit(landop_expr_syntax &node)
{
    // exit(101);
    auto temp_cond_then_bb = cond_then_bb;
    auto next_and_bb = BasicBlock::Create(context, "next_and_bb" + std::to_string(bb_count++), current_function);
    cond_then_bb = next_and_bb;
    node.land_expr->accept(*this);
    builder.SetInsertPoint(next_and_bb);
    cond_then_bb = temp_cond_then_bb;
    Icmp_expected = true;
    node.eq_expr->accept(*this);
    Icmp_expected = false;
}

void assembly_builder::visit(eqop_expr_syntax &node)
{
    Icmp_expected = false;
    node.eq_expr->accept(*this);
    auto result_1 = value_result;
    result_1 = CastToInt32(result_1);
    node.rel_expr->accept(*this);
    auto result_2 = value_result;
    result_2 = CastToInt32(result_2);
    if(node.op==relop::equal){
        value_result=builder.CreateICmpEQ(result_1,result_2);
    }
    else if(node.op==relop::non_equal){
        value_result=builder.CreateICmpNE(result_1,result_2);
    }
    builder.CreateCondBr(value_result,cond_then_bb,cond_else_bb);
}

void assembly_builder::visit(rel_expr_syntax &node)
{
    if(node.rel_expr){
        Icmp_expected = false;
        node.rel_expr->accept(*this);
        auto left_value = CastToInt32(value_result);
        if(left_value->getType()->getTypeID() == Type::getInt32PtrTy(context)->getTypeID()){
            error_flag = true;
            err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                        "Type of left value is pointer");
            return;
        }
        Icmp_expected = false;
        node.add_expr->accept(*this);
        auto right_value = CastToInt32(value_result);
        if(right_value->getType()->getTypeID() == Type::getInt32PtrTy(context)->getTypeID()){
            error_flag = true;
            err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                        "Type of left value is pointer");
            return;
        }
        if(left_value->getType()->getTypeID()!=right_value->getType()->getTypeID()){
            error_flag = true;
            err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                        "Types of left and right value are not same");
            return;
        }
        switch(node.op)
        {
            case relop::greater:
                value_result = builder.CreateICmpSGT(left_value,right_value);
                break;
            case relop::greater_equal:
                value_result = builder.CreateICmpSGE(left_value,right_value);
                break;
            case relop::less:
                value_result = builder.CreateICmpSLT(left_value,right_value);
                break;
            case relop::less_equal:
                value_result = builder.CreateICmpSLE(left_value,right_value);
                break;
            default:
                break;
        }
        builder.CreateCondBr(value_result,cond_then_bb,cond_else_bb);
    }
    else{

        // std::cout << "inside second branch, find value " << std::endl;

        node.add_expr->accept(*this);
        if(Icmp_expected){

            // std::cout << "inside second branch, value to bool " << std::endl;

            auto Icmp_result = CastToBoolean(value_result);
            builder.CreateCondBr(Icmp_result, cond_then_bb, cond_else_bb);
        }

        // std::cout << "leave inside second branch, find value " << std::endl;
    }
}

void assembly_builder::visit(assign_stmt_syntax &node)
{
    // get target address
    lval_as_rval = false;
    node.target->accept(*this);
    auto target_address = value_result;

    // read assigned value
    lval_as_rval = true;
    constexpr_expected = false;
    node.value->accept(*this);
    auto assign_value = value_result;
    builder.CreateStore(assign_value, target_address);
}

void assembly_builder::visit(block_syntax &node)
{
    enter_scope();
    auto children = node.body;
    for (auto &child : children) 
    {
        constexpr_expected = false;
        child->accept(*this);
    }
    exit_scope();
}

void assembly_builder::visit(expr_stmt_syntax &node)
{
    if(node.expr){
        node.expr->accept(*this);
    }
}

void assembly_builder::visit(if_stmt_syntax &node)
{
    // define basic blocks
    // auto if_bb   = BasicBlock::Create(context, "if_bb" + std::to_string(bb_count++), current_function);
    auto then_bb = BasicBlock::Create(context, "then_bb" + std::to_string(bb_count++), current_function);
    auto else_bb = BasicBlock::Create(context, "else_bb" + std::to_string(bb_count++), current_function);
    auto next_bb = BasicBlock::Create(context, "if_next_bb" + std::to_string(bb_count++), current_function);

    // condition
    // builder.CreateBr(if_bb);
    // builder.SetInsertPoint(if_bb);
    if (node.else_body) {
        cond_then_bb = then_bb;
        cond_else_bb = else_bb;
    }
    else {
        cond_then_bb = then_bb;
        cond_else_bb = next_bb;
    }
    Icmp_expected = true;
    node.pred->accept(*this);
    // if (node.else_body) builder.CreateCondBr(value_result, then_bb, else_bb);
    // else builder.CreateCondBr(value_result, then_bb, next_bb);

    // then
    builder.SetInsertPoint(then_bb);
    node.then_body->accept(*this);

    if(builder.getInsertBlock()->getTerminator() == nullptr){
        builder.CreateBr(next_bb);
    }

    if (node.else_body == nullptr) {
        else_bb->removeFormParent();
    } else {
        builder.SetInsertPoint(else_bb);
        node.else_body->accept(*this);
        if (builder.getInsertBlock()->getTerminator() == nullptr)
            builder.CreateBr(next_bb);
    }
    // set insert point to the correct location
    builder.SetInsertPoint(next_bb);
}

void assembly_builder::visit(while_stmt_syntax &node)
{
    // define basic blocks
    auto while_block = BasicBlock::Create(context, "cond_while" + std::to_string(bb_count++), current_function);
    auto while_body  = BasicBlock::Create(context, "body_while" + std::to_string(bb_count++), current_function);
    auto while_next  = BasicBlock::Create(context, "next_while" + std::to_string(bb_count++), current_function);
    
    // FIXME:
    // Should Set continue points to while_block or while_body?
    SetWhileBlocks(while_block,while_next);
    builder.CreateBr(while_block);
    builder.SetInsertPoint(while_block);
    // generate codes for condition
    cond_then_bb = while_body;
    cond_else_bb = while_next;
    Icmp_expected = true;
    node.pred->accept(*this);

    builder.SetInsertPoint(while_body);
    // generate codes for body
    node.body->accept(*this);

    builder.CreateBr(while_block);

    LeaveWhieBlocks();
    // set insert point to the correct location
    builder.SetInsertPoint(while_next);
}

void assembly_builder::visit(break_stmt_syntax &node)
{
    if(!SetBreak()){
        error_flag = true;
        err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                "Not inside any while loop.");
        return;
    }
}

void assembly_builder::visit(continue_stmt_syntax &node)
{
    if(!SetContinue()){
        error_flag = true;
        err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
                "Not inside any while loop.");
        return;
    }
}

void assembly_builder::visit(return_stmt_syntax &node)
{
    if(current_function->getReturnType() == Type::getVoidTy(context) && node.expr==nullptr){
        builder.CreateRetVoid();
        return;   
    }
    if(current_function->getReturnType() == Type::getInt32Ty(context) && node.expr){
        node.expr->accept(*this);
        builder.CreateRet(value_result);
        // std::cout << "Insert Return I32 successed"<< std::endl;
        return;
    }
    error_flag = true;
    err.error(static_cast<size_t>(node.line), static_cast<size_t>(node.pos),
            "Return Statement disagrees with its function's decleration.");
    return;
}

void assembly_builder::visit(func_def_param_syntax &node) {}