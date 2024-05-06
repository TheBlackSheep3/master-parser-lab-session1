#include "EvaluationVisitor.h"
#include <any>

std::any EvaluationVisitor::visitFactor(ExpressionParser::FactorContext *ctx) {
  if (ctx->NUMBER()) {
    return std::stoi(ctx->NUMBER()->getText());
  } else {
    return visitExpression(ctx->expression());
  }
}
std::any
EvaluationVisitor::visitExpression(ExpressionParser::ExpressionContext *ctx) {
  if (ctx->PLUS()) {
    return std::any_cast<int>(visitTerm(ctx->term())) + std::any_cast<int>(visitExpression(ctx->expression()));
  } else {
    return visitTerm(ctx->term());
  }
}
std::any EvaluationVisitor::visitTerm(ExpressionParser::TermContext *ctx) {
  if (ctx->TIMES()) {
    return std::any_cast<int>(visitFactor(ctx->factor())) * std::any_cast<int>(visitTerm(ctx->term()));
  } else {
    return visitFactor(ctx->factor());
  }
}
