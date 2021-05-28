#include "node.h"


bool EmptyNode::Evaluate(const Date& d, const std::string&) {
    return true;
}


DateComparisonNode::DateComparisonNode(Comparison cmp, const Date& date) 
    : cmp_(cmp), date_(date) {}

bool DateComparisonNode::Evaluate(const Date& date, const std::string&) {
    if (cmp_ == Comparison::Equal) return date == date_;
    if (cmp_ == Comparison::Less) return date < date_;
    if (cmp_ == Comparison::Greater) return date > date_;
    if (cmp_ == Comparison::LessOrEqual) return date <= date_;
    if (cmp_ == Comparison::GreaterOrEqual) return date >= date_;       
    if (cmp_ == Comparison::NotEqual) return date != date_;
    return false;
}


EventComparisonNode::EventComparisonNode(Comparison cmp, const std::string& event)
    : cmp_(cmp), event_(event) {}

bool EventComparisonNode::Evaluate(const Date&, const std::string& event) {
    if (cmp_ == Comparison::Equal) return event == event_;
    if (cmp_ == Comparison::NotEqual) return event != event_;
    if (cmp_ == Comparison::Less) return event < event_;
    if (cmp_ == Comparison::LessOrEqual) return event <= event_;
    if (cmp_ == Comparison::Greater) return event > event_;
    if (cmp_ == Comparison::GreaterOrEqual) return event >= event_;
    return false;
}


LogicalOperationNode::LogicalOperationNode(LogicalOperation op, std::shared_ptr<Node> l, std::shared_ptr<Node> r)
    : op_(op), l_(l), r_(r) {}

bool LogicalOperationNode::Evaluate(const Date& date, const std::string& event) {
    if (op_ == LogicalOperation::Or) {
        return l_->Evaluate(date, event) || r_->Evaluate(date, event);
    } else if (op_ == LogicalOperation::And) {
        return l_->Evaluate(date, event) && r_->Evaluate(date, event);
    }
    return false;
}


