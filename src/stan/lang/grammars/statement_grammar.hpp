#ifndef STAN_LANG_GRAMMARS_STATEMENT_GRAMMAR_HPP
#define STAN_LANG_GRAMMARS_STATEMENT_GRAMMAR_HPP

#include <stan/lang/ast.hpp>
#include <stan/lang/grammars/expression_grammar.hpp>
#include <stan/lang/grammars/indexes_grammar.hpp>
#include <stan/lang/grammars/semantic_actions.hpp>
#include <stan/lang/grammars/statement_2_grammar.hpp>
#include <stan/lang/grammars/whitespace_grammar.hpp>
#include <stan/lang/grammars/var_decls_grammar.hpp>
#include <boost/spirit/include/qi.hpp>
#include <sstream>
#include <string>
#include <vector>

namespace stan {

  namespace lang {

    template <typename Iterator>
    struct statement_grammar
      : boost::spirit::qi::grammar<Iterator,
                                   statement(bool, var_origin, bool),
                                   whitespace_grammar<Iterator> > {
      statement_grammar(variable_map& var_map,
                        std::stringstream& error_msgs);

      variable_map& var_map_;
      std::stringstream& error_msgs_;
      expression_grammar<Iterator> expression_g;
      var_decls_grammar<Iterator> var_decls_g;
      statement_2_grammar<Iterator> statement_2_g;
      indexes_grammar<Iterator> indexes_g;

      boost::spirit::qi::rule<Iterator,
                              assignment(var_origin),
                              whitespace_grammar<Iterator> >
      assignment_r;

      boost::spirit::qi::rule<Iterator,
                              assgn(var_origin),
                              whitespace_grammar<Iterator> >
      assgn_r;

      boost::spirit::qi::rule<Iterator,
                              boost::spirit::qi::unused_type,
                              whitespace_grammar<Iterator> >
      assignment_operator_r;


      boost::spirit::qi::rule<Iterator,
                              expression(var_origin),
                              whitespace_grammar<Iterator> >
      non_lvalue_assign_r;


      boost::spirit::qi::rule<Iterator,
                              std::vector<expression>(var_origin),
                              whitespace_grammar<Iterator> >
      dims_r;

      boost::spirit::qi::rule<Iterator,
                              variable(var_origin),
                              whitespace_grammar<Iterator> >
      var_r;


      boost::spirit::qi::rule<Iterator,
                              distribution(var_origin),
                              whitespace_grammar<Iterator> >
      distribution_r;


      boost::spirit::qi::rule<Iterator,
                              increment_log_prob_statement(bool, var_origin),
                              whitespace_grammar<Iterator> >
      increment_log_prob_statement_r;

      boost::spirit::qi::rule<Iterator,
                              boost::spirit::qi::locals<std::string>,
                              for_statement(bool, var_origin, bool),
                              whitespace_grammar<Iterator> >
      for_statement_r;


      boost::spirit::qi::rule<Iterator,
                              while_statement(bool, var_origin, bool),
                              whitespace_grammar<Iterator> >
      while_statement_r;


      boost::spirit::qi::rule<Iterator,
                              print_statement(var_origin),
                              whitespace_grammar<Iterator> >
      print_statement_r;

      boost::spirit::qi::rule<Iterator,
                              reject_statement(var_origin),
                              whitespace_grammar<Iterator> >
      reject_statement_r;


      boost::spirit::qi::rule<Iterator,
                              return_statement(var_origin),
                              whitespace_grammar<Iterator> >
      return_statement_r;

      boost::spirit::qi::rule<Iterator,
                              return_statement(var_origin),
                              whitespace_grammar<Iterator> >
      void_return_statement_r;

      boost::spirit::qi::rule<Iterator,
                              printable(var_origin),
                              whitespace_grammar<Iterator> >
      printable_r;

      boost::spirit::qi::rule<Iterator,
                              std::string(),
                              whitespace_grammar<Iterator> >
      printable_string_r;


      boost::spirit::qi::rule<Iterator,
                              std::string(),
                              whitespace_grammar<Iterator> >
      identifier_r;

      boost::spirit::qi::rule<Iterator,
                              std::vector<var_decl>(),
                              whitespace_grammar<Iterator> >
      local_var_decls_r;

      boost::spirit::qi::rule<Iterator,
                              no_op_statement(),
                              whitespace_grammar<Iterator> >
      no_op_statement_r;

      boost::spirit::qi::rule<Iterator,
                              std::vector<expression>(var_origin),
                              whitespace_grammar<Iterator> >
      opt_dims_r;

      boost::spirit::qi::rule<Iterator,
                              range(var_origin),
                              whitespace_grammar<Iterator> >
      range_r;

      boost::spirit::qi::rule<Iterator,
                              sample(bool, var_origin),
                              whitespace_grammar<Iterator> >
      sample_r;

      boost::spirit::qi::rule<Iterator,
                              statement(bool, var_origin, bool),
                              whitespace_grammar<Iterator> >
      statement_r;

      boost::spirit::qi::rule<Iterator,
                              statement(bool, var_origin, bool),
                              whitespace_grammar<Iterator> >
      statement_sub_r;

      boost::spirit::qi::rule<Iterator,
                              boost::spirit::qi::locals<std::vector<var_decl> >,
                              statements(bool, var_origin, bool),
                              whitespace_grammar<Iterator> >
      statement_seq_r;

      boost::spirit::qi::rule<Iterator,
                              range(var_origin),
                              whitespace_grammar<Iterator> >
      truncation_range_r;

      boost::spirit::qi::rule<Iterator,
                              variable_dims(var_origin),
                              whitespace_grammar<Iterator> >
      var_lhs_r;

      boost::spirit::qi::rule<Iterator,
                              expression(var_origin),
                              whitespace_grammar<Iterator> >
      expression_rhs_r;
    };

  }
}
#endif
