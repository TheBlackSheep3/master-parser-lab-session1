#pragma once

#include "antlr4-runtime.h"
#include "ExpressionBaseVisitor.h"

class EvaluationVisitor : public ExpressionBaseVisitor {
	public:
  virtual std::any visitExpression(ExpressionParser::ExpressionContext *ctx) override;
  virtual std::any visitTerm(ExpressionParser::TermContext *ctx) override;
  virtual std::any visitFactor(ExpressionParser::FactorContext *ctx) override;
};
