//
// Created by sobral on 27/07/19.
//
#include <limits.h>
#include <time.h>
#include <string>
#include <algorithm>
#include <queue>
#include "enfileira.h"
#include "gtest/gtest.h"

using std::string;
using std::to_string;
using std::queue;

class TesteEnfileira: public ::testing::Test {
protected:
    virtual void SetUp() {
        srand(clock());
    }

    string gen_string() {
        string s;
        int n;

        n = 2 + (rand() % 32);
        while (n-- > 0) s += (char)('a'+(rand() % 26));
        return s;
    }

    bool verifica(queue<char> q, const string & s) {
        for (auto & c: s) {
            if (c != q.front()) return false;
            q.pop();
        }
        return true;
    }

    string fila2str(queue<char> & q) {
        string s;

        while (! q.empty()) {
            s += q.front();
            q.pop();
        }

        return s;
    }
};

/*::testing::AssertionResult AssertSubstitui(const char* texto_expr,
                                               const char* sub_expr,
                                               const char* outra_expr,
                                               const char* correto_expr,
                                               const string & texto,
                                               const string & sub,
                                               const string & outra,
                                               const string & correto) {
    string res = substitui(texto, sub, outra);
    if (res == correto) return ::testing::AssertionSuccess();

    return ::testing::AssertionFailure() << "texto=" << texto << ", " << sub_expr << "=" << sub << ", " << outra_expr << "=" << outra << ": "
                                         << " resultado deveria ser: " << correto
                                         << ", mas sua função retornou: " << res;
}
*/

TEST_F(TesteEnfileira, Vazia) {
    try {
        queue<char> q;
        enfileira_chars("", q);

        if (q.size() > 0) {
            FAIL() << "queue tem tamanho maior que 0 após enfileirar caracteres de uma string vazia";
        }

    } catch (...) {
        FAIL() << "ocorreu uma exceção";
    }

}

TEST_F(TesteEnfileira, Simples) {
    for (int i=0; i < 10; i++) {
        try {
            queue<char> q;
            string data;
            data += 'A' + (rand() % 26);
            enfileira_chars(data, q);

            if (q.size() != 1) {
                FAIL() << "queue tem tamanho " << to_string(q.size()) << ", mas deveria ter tamanho 1";
                return;
            }

            if (! verifica(q, data)) {
                FAIL() << "Caracteres da fila diferente da string. A string contém " << data
                << ", e a fila contém " << fila2str(q);
            }

        } catch (...) {
            FAIL() << "ocorreu uma exceção";
        }
    }
}

TEST_F(TesteEnfileira, Normal) {
    try {
        for (int n=0; n < 10; n++) {
            queue<char> q;
            string s = gen_string();
            enfileira_chars(s, q);

            if (q.size() != s.size()) {
                FAIL() << "queue tem tamanho "+to_string(q.size())+", mas deveria ter size "+to_string(s.size())+": palavra="+s;
            }

            if (! verifica(q, s)) {
                FAIL() << "Caracteres da fila diferente da string. A string contém " << s
                       << ", e a fila contém " << fila2str(q);
            }
        }
    } catch (...) {
        FAIL() << "ocorreu uma exceção";
    }
}
