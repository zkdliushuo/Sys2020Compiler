#ifndef CODEGEN_LABELTABLE_H
#define CODEGEN_LABELTABLE_H

#include <string>
#include <vector>

namespace labeltable {

class Label;
class LabelTable;

class Label {
public:
  enum LabelType { Function = 0, BasicBlock };

private:
  std::string label_name;
  LabelType label_type;
  int label_address;
  LabelTable *father_table;

public:
  Label(std::string name, int type, LabelTable *father) {
    label_name = name;
    if (!type)
      label_type = LabelType::Function;
    else
      label_type = LabelType::BasicBlock;
    label_address = 0; // default
    father_table = father;
  }
  ~Label() = default;

  std::string getLabelName() const { return label_name; }
  LabelType getLabelType() const { return label_type; }

  void updateLabelName(std::string new_name) { label_name = new_name; }
  void updateLabelType(int new_type) {
    if (!new_type)
      label_type = LabelType::Function;
    else
      label_type = LabelType::BasicBlock;
  }
};

class LabelTable {
private:
  std::vector<Label *> label_table;

public:
  LabelTable() { label_table.clear(); }
  ~LabelTable() {
    for (auto label_item : label_table) {
      delete label_item;
    }
  }

  bool inLabelTable(std::string label) const {
    for (auto label_item : label_table) {
      if (label_item->getLabelName() == label)
        return true;
      else
        return false;
    }
  }

  void addFunctionLabel(std::string label) {
    Label *function_label = new Label(label, 0, this);
    label_table.push_back(function_label);
  }
  void addBasicBlockLabel(std::string label) {
    Label *basic_block_label = new Label(label, 1, this);
    label_table.push_back(basic_block_label);
  }
  // TODO: delete a label
};
} // namespace labeltable

#endif