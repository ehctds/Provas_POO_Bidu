/*
* Sistema de pagamentos

Crie uma classe pagamento que represente um pagamento genérico.
- campos: valor, data, numero_cartao
Crie uma classe pagamento_online que herde da classe pagamento.
- campos: nome_site, codigo_seguranca
Crie uma classe pagamento_presencial que herde da classe pagamento.
- campos: nome_loja
Crie uma classe template fatura que represente uma fatura com multiplos
pagamentos (online ou presencial). 
- A classe deve ter um campo double limite_credito que representa o limite
- A classe deve ter um campo vector de pagamentos. 
- A classe deve ter um método adicionar_pagamento() que recebe como parâmetro 
um pagamento e o adiciona ao vector de pagamentos.
- A classe deve ter um método calcular_valor_total() que calcula o valor total
da fatura com base nos pagamentos adicionados.

Sobrecarregue o operador << para imprimir as informações de um objeto da classe fatura.
Sobrecarregue o operador + para adicionar um pagamento a uma fatura.
Sobrecarregue o operador - para remover um pagamento de uma fatura.

Crie uma função friend template chamada transferir_pagamentos() que receba como parâmetros
dois objetos da classe fatura (com o mesmo tipo template) e transfira todos os pagamentos
da primeira fatura para a segunda fatura.

Adicione tratamento de exceções ao código para lidar com situações em que o usuário tente
adicionar pagamentos acima do limite (campo limite_credito).

Crie uma funcao main que crie três objetos da classe fatura, com pelo menos três pagamentos
cada. Imprima as informações de cada fatura e transfira os pagamentos da primeira fatura
para a segunda fatura. Imprima novamente as informações de cada fatura.
*/

#include <iostream>
#include <vector>
#include <string>

class Pagamento { // classe abstrata
protected:
    double valor;
    std::string data;
    std::string numeroCartao;
// construtor e destrutor são protected para evitar que a classe seja instanciada
public:
    Pagamento(double valor, std::string data, std::string numeroCartao) :
        valor(valor), data(data), numeroCartao(numeroCartao) {} // construtor
    
    // destrutor virtual para permitir que as classes derivadas sejam destruídas corretamente
    virtual ~Pagamento() {}

    double getValor() {
        return valor;
    }
    std::string getData() {
        return data;
    }

    std::string getNumeroCartao() {
        return numeroCartao;
    }
};

class PagamentoOnline : public Pagamento { // classe derivada
    std::string nomeSite;
    std::string codigoSeguranca;
public:
    PagamentoOnline(double valor, std::string data, std::string numeroCartao,
                     std::string nomeSite, std::string codigoSeguranca) :
        Pagamento(valor, data, numeroCartao), nomeSite(nomeSite),
        codigoSeguranca(codigoSeguranca) {} // construtor
    std::string getNomeSite() {
        return nomeSite;
    }

    std::string getCodigoSeguranca() {
        return codigoSeguranca;
    }
};

class PagamentoPresencial : public Pagamento {
    std::string nomeLoja;
public:
    PagamentoPresencial(double valor, std::string data, std::string numeroCartao,
                         std::string nomeLoja) :
        Pagamento(valor, data, numeroCartao), nomeLoja(nomeLoja) {}

    std::string getNomeLoja() {
        return nomeLoja;
    }
};

template <typename T> // T é um tipo genérico que representa o tipo de pagamento a ser armazenado
class Fatura { // classe genérica
    double limiteCredito;
    std::vector<T*> pagamentos; // vetor dinâmico de ponteiros para pagamentos

public:
    Fatura(double limiteCredito) : limiteCredito(limiteCredito) {}
    ~Fatura() {
        for (typename std::vector<T*>::iterator it = pagamentos.begin(); it != pagamentos.end(); ++it) {
            delete *it;
        }
    } // destrutor

    void adicionarPagamento(T* pagamento) {
        if (calcularValorTotal() + pagamento->getValor() > limiteCredito) { // verifica se o limite de crédito foi excedido
            throw std::string("Limite de crédito excedido!"); // lança uma exceção
        }
        pagamentos.push_back(pagamento);
    } // adiciona um pagamento ao vetor pagamentos

    void removerPagamento(int indice) {
        if (indice >= 0 && indice < pagamentos.size()) {
            pagamentos.erase(pagamentos.begin() + indice);
        } // remove um pagamento do vetor pagamentos
        else {
            throw std::string("Índice inválido!"); // lança uma exceção caso seja invalido o indice
        }
    }

    double calcularValorTotal() {
        double total = 0;
        for (typename std::vector<T*>::iterator it = pagamentos.begin(); it != pagamentos.end(); ++it) { // itera sobre o vetor pagamentos
            total += (*it)->getValor(); // soma o valor de cada pagamento ao total
        }
        return total;
    }

    friend std::ostream& operator<<(std::ostream& os, const Fatura<T>& f) { // sobrecarga do operador de inserção <<
        for (typename std::vector<T*>::const_iterator it = f.pagamentos.begin(); it != f.pagamentos.end(); ++it) { 
            os << "Valor: " << (*it)->getValor() << " | Data: " << (*it)->getData() << " | "; // imprime o valor e a data do pagamento
            if (dynamic_cast<PagamentoOnline*>(*it) != nullptr) { // verifica dinamicamente se o pagamento é do tipo PagamentoOnline
                os << "Tipo: Pagamento Online";
                os << " | Site: " << dynamic_cast<PagamentoOnline*>(*it)->getNomeSite(); // imprime o nome do site
                os << " | Código de Segurança: " << dynamic_cast<PagamentoOnline*>(*it)->getCodigoSeguranca(); // imprime o código de segurança
            }
            else if (dynamic_cast<PagamentoPresencial*>(*it) != nullptr) { // verifica dinamicamente se o pagamento é do tipo PagamentoPresencial
                os << "Tipo: Pagamento Presencial";
                os << " | Loja: " << dynamic_cast<PagamentoPresencial*>(*it)->getNomeLoja(); // imprime o nome da loja
            }
            os << std::endl;
        }
        return os;
    }

    Fatura<T>& operator+(T* pagamento) { // sobrecarga do operador +
        adicionarPagamento(pagamento); // adiciona o pagamento ao vetor pagamentos
        return *this; // retorna a própria instância da fatura para permitir encadeamento de operações
    }

    Fatura<T>& operator-(int indice) { // sobrecarga do operador -
        removerPagamento(indice); // remove o pagamento do vetor pagamentos
        return *this; // retorna a própria instância da fatura para permitir encadeamento de operações
    }

    friend void transferirPagamentos(Fatura<T>& faturaOrigem, Fatura<T>& faturaDestino) { // função externa amiga
        for (typename std::vector<T*>::iterator it = faturaOrigem.pagamentos.begin(); it != faturaOrigem.pagamentos.end(); ++it) { // itera sobre o vetor pagamentos da fatura de origem
            faturaDestino.adicionarPagamento(*it); // adiciona o pagamento à fatura de destino
        }
        faturaOrigem.pagamentos.clear(); // limpa o vetor pagamentos da fatura de origem
    }
};

int main() {
    try {
        Fatura<Pagamento> fatura1(100000.0);
        Fatura<Pagamento> fatura2(1000000.0);
        Fatura<Pagamento> fatura3(85000.0);

        Pagamento* pagamento1 = new PagamentoOnline(3000.0, "2023-02-13", "1234567890", "SiteA", "123");
        Pagamento* pagamento2 = new PagamentoPresencial(12000.0, "2023-03-14", "0987654321", "LojaA");
        Pagamento* pagamento3 = new PagamentoOnline(5000.0, "2023-03-16", "2468135790", "SiteB", "456");
        Pagamento* pagamento4 = new PagamentoPresencial(15000.0, "2023-06-16", "1357924680", "LojaB");
        Pagamento* pagamento5 = new PagamentoOnline(34000.0, "2023-06-19", "8024681359", "SiteC", "789");
        Pagamento* pagamento6 = new PagamentoPresencial(4000.0, "2023-06-21", "5793146820", "LojaC");
        Pagamento* pagamento7 = new PagamentoOnline(10000.0, "2023-06-30", "4681357920", "SiteD", "012");

        fatura1.adicionarPagamento(pagamento1);
        fatura1.adicionarPagamento(pagamento2);
        fatura1.adicionarPagamento(pagamento3);

        fatura2.adicionarPagamento(pagamento4);
        fatura2.adicionarPagamento(pagamento5);

        fatura3.adicionarPagamento(pagamento6);
        fatura3.adicionarPagamento(pagamento7);

        std::cout << "Fatura 1:\n" << fatura1 << std::endl;
        std::cout << "Fatura 2:\n" << fatura2 << std::endl;
        std::cout << "Fatura 3:\n" << fatura3 << std::endl;

        transferirPagamentos(fatura1, fatura2);

        std::cout << "Após transferir pagamentos da Fatura 1 para Fatura 2:\n";
        std::cout << "Fatura 1:\n" << fatura1 << std::endl;
        std::cout << "Fatura 2:\n" << fatura2 << std::endl;
        std::cout << "Fatura 3:\n" << fatura3 << std::endl;

        std::cout << "Valor total da Fatura 1: " << fatura1.calcularValorTotal() << std::endl;
        std::cout << "Valor total da Fatura 2: " << fatura2.calcularValorTotal() << std::endl;
        std::cout << "Valor total da Fatura 3: " << fatura3.calcularValorTotal() << std::endl;
    }
    catch (std::string e) {
        std::cout << "Erro: " << e << std::endl; // imprime a mensagem de erro
    }

    return 0;
}


/*
comentarios sobre a classe Fatura: 
1) é um tipo genérico que permite gerenciar pagamentos de diferentes tipos. Ela é parametrizada com o tipo T, 
que representa o tipo de pagamento a ser armazenado.

2) o construtor recebe o limite de crédito da fatura.

3) Dentro da classe, temos um vetor dinâmico pagamentos do tipo T*, 
que armazena os ponteiros para os pagamentos registrados.

4) o destrutor libera a memória alocada para os pagamentos.

5) O operador de inserção << é sobrecarregado para permitir a exibição dos detalhes dos pagamentos e 
da fatura no console. Ele itera sobre o vetor pagamentos e imprime as informações de cada pagamento, verificando 
dinamicamente se o pagamento é do tipo PagamentoOnline ou PagamentoPresencial para exibir os atributos específicos.

6) Os operadores + e - são sobrecarregados para permitir a adição e remoção de pagamentos de forma mais intuitiva. 
Eles chamam as funções adicionarPagamento e removerPagamento, respectivamente, e retornam a própria instância da fatura 
para permitir encadeamento de operações.

7)A função transferirPagamentos é uma função externa amiga que recebe duas instâncias de Fatura como parâmetros. 
Ela itera sobre os pagamentos da fatura de origem e os adiciona à fatura de destino, utilizando a função adicionarPagamento. 
Em seguida, limpa o vetor pagamentos da fatura de origem.

*/