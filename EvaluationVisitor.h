#pragma once

#include "ExpressionBaseVisitor.h"
#include "antlr4-runtime.h"

class EvaluationVisitor : public ExpressionBaseVisitor {
public:
  virtual std::any visitStart(ExpressionParser::StartContext *ctx) override;
  virtual std::any visitExpression(ExpressionParser::ExpressionContext *ctx) override;
  virtual std::any visitExpressionPrime(ExpressionParser::ExpressionPrimeContext *ctx) override;
  virtual std::any visitTerm(ExpressionParser::TermContext *ctx) override;
  virtual std::any visitTermPrime(ExpressionParser::TermPrimeContext *ctx) override;
  virtual std::any visitFactor(ExpressionParser::FactorContext *ctx) override;
};
