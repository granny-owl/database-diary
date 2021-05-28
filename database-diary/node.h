#pragma once
#include "enums.h"
#include "date.h"
#include <string>
#include <vector>
#include <memory>


class Node {
public:
    virtual ~Node() = default;
    virtual bool Evaluate(const Date& d, const std::string& s) = 0;
};


class EmptyNode : public Node {
public:
    bool Evaluate(const Date& d, const std::string&) override;
};


class DateComparisonNode : public Node {
    const Comparison cmp_;
    const Date date_;
public:
    DateComparisonNode(Comparison cmp, const Date& date);
    bool Evaluate(const Date& d, const std::string&) override;
};


class EventComparisonNode : public Node {
    const Comparison cmp_;
    const std::string event_;
public:
    EventComparisonNode(Comparison cmp, const std::string& event);
    bool Evaluate(const Date&, const std::string& event) override;
};


class LogicalOperationNode : public Node {
    std::shared_ptr<Node> l_, r_;
    const LogicalOperation op_;
public:
    LogicalOperationNode(LogicalOperation op, std::shared_ptr<Node> l, std::shared_ptr<Node> r);
    bool Evaluate(const Date& d, const std::string& ev) override;
};