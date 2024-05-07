#include "EvaluationVisitor.h"
#include <any>

std::any EvaluationVisitor::visitStart(ExpressionParser::StartContext *ctx) {
  return visitExpression(ctx->expression());
}
std::any
EvaluationVisitor::visitExpression(ExpressionParser::ExpressionContext *ctx) {
  return std::any_cast<int>(visitTerm(ctx->term())) +
         std::any_cast<int>(visitExpressionPrime(ctx->expressionPrime()));
}
std::any EvaluationVisitor::visitExpressionPrime(
    ExpressionParser::ExpressionPrimeContext *ctx) {
  if (ctx->PLUS()) {
    return visitExpression(ctx->expression());
  } else {
    return 0;
  }
}
std::any EvaluationVisitor::visitTerm(ExpressionParser::TermContext *ctx) {
  return std::any_cast<int>(visitFactor(ctx->factor())) *
         std::any_cast<int>(visitTermPrime(ctx->termPrime()));
}
std::any
EvaluationVisitor::visitTermPrime(ExpressionParser::TermPrimeContext *ctx) {
  if (ctx->TIMES()) {
    return visitTerm(ctx->term());
  } else {
    return 1;
  }
}
std::any EvaluationVisitor::visitFactor(ExpressionParser::FactorContext *ctx) {
  if (ctx->NUMBER()) {
    return std::stoi(ctx->NUMBER()->getText());
  } else {
    return visitExpression(ctx->expression());
  }
}
