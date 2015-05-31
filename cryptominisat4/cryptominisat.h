/******************************************
Copyright (c) 2014, Mate Soos

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
***********************************************/

#ifndef __CRYPTOMINISAT4_H__
#define __CRYPTOMINISAT4_H__

#include <vector>
#include <iostream>
#include <utility>
#include "cryptominisat4/solvertypesmini.h"

namespace CMSat {
    struct CMSatPrivateData;
    class SATSolver
    {
    public:
        SATSolver(void* config = NULL, bool* interrupt_asap = NULL);
        ~SATSolver();
        void set_num_threads(unsigned n);
        unsigned nVars() const;
        bool add_clause(const std::vector<Lit>& lits);
        bool add_xor_clause(const std::vector<unsigned>& vars, bool rhs);
        void new_var();
        void new_vars(const size_t n);
        lbool solve(const std::vector<Lit>* assumptions = 0);
        const std::vector<lbool>& get_model() const;
        const std::vector<Lit>& get_conflict() const;
        void add_sql_tag(const std::string& tagname, const std::string& tag);
        unsigned long get_sql_id() const;
        bool okay() const;
        void log_to_file(std::string filename);

        //Setup
        void set_max_confl(int64_t max_confl = -1);
        void set_verbosity(unsigned verbosity = 0);
        void set_default_polarity(bool polarity);

        //Get info
        static const char* get_version();
        static const char* get_version_sha1();
        static const char* get_compilation_env();

        void print_stats() const;
        void set_drup(std::ostream* os);
        void interrupt_asap();
        void open_file_and_dump_irred_clauses(std::string fname) const;
        void open_file_and_dump_red_clauses(std::string fname) const;
        void add_in_partial_solving_stats();

        std::vector<Lit> get_zero_assigned_lits() const;
        std::vector<std::pair<Lit, Lit> > get_all_binary_xors() const;
    private:
        CMSatPrivateData *data;
    };
}

#endif //__CRYPTOMINISAT4_H__
