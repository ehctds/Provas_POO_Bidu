#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Conta {   /*classe conta criada utilizando os atributos da questão*/
private:
    int numero;
    float saldo;
    string titular;
public:
    Conta(int n, float s, string t) {
        numero = n;
        saldo = s;
        titular = t;
        cout << "Conta criada com sucesso" << endl;
        cout << "Numero: " << numero << endl;
        cout << "Titular: " << titular << endl;
        cout << "Saldo: " << saldo << endl;
        cout << endl;
    }
    void sacar(float valor) {  /*função sacar criada para realizar o saque*/
        if (valor <= saldo) {
            saldo -= valor;
            cout << "Saque realizado com sucesso" << endl;
        } else {
            cout << "Saldo insuficiente" << endl;
        }
        cout << "Novo saldo: " << saldo << endl << endl;
    }
    void depositar(float valor) {   /*função depositar criada para realizar o deposito*/
        saldo += valor;
        cout << "Deposito realizado com sucesso" << endl;
        cout << "Novo saldo: " << saldo << endl << endl;
    }
    int getNumero() const {
        return numero;
    }
    float getSaldo() const {
        return saldo;
    }
    string getTitular() const {
        return titular;
    }
};

class ContaCorrente : public Conta {  /*classe conta corrente criada utilizando os atributos da classe conta*/
private:
    float limite;
public:
    ContaCorrente(int n, float s, string t, float l) : Conta(n, s, t) {
        limite = l;
    }
    void sacar(float valor){
        if (valor <= getSaldo() + limite) {
            Conta::sacar(valor);
        } else {
            cout << "Saldo insuficiente" << endl;
        }
    }
};

class ContaPoupanca : public Conta {  /*classe conta poupança criada utilizando os atributos da classe conta*/
private:
    float rendimento;
public:
    ContaPoupanca(int n, float s, string t, float r) : Conta(n, s, t) {
        rendimento = r;
    }
    void atualizaRendimento() {
        depositar(getSaldo() * rendimento);
    }
};

class Banco {  /*classe banco criada utilizando os atributos da questão e o array dinamico*/
private:
    vector<Conta*> contas;  /*array dinamico criado para armazenar as contas criadas*/
public:
    Banco() {}
    ~Banco() {
        for (auto c : contas) {
            delete c;
        }  /* Método destrutor para remover o memory leak gerando por um array dinamico*/
    }
    void adicionarConta(Conta* c) {
        contas.push_back(c); 
          /* o pushbakc tem a finalidade de 
          Adiciona um novo elemento no final do vetor, 
          apos seu utimo elemento atual*/
    }
    void listarContas() const {
        for (auto c : contas) {
            cout << "Numero: " << c->getNumero() << endl;
            cout << "Titular: " << c->getTitular() << endl;
            cout << "Saldo: " << c->getSaldo() << endl << endl;
        }
    } /*função listar contas criada para listar as contas criadas*/
};

int main() {
    Banco banco;
    
    ContaCorrente cc1(1, 1000, "Joao", 500);
    ContaPoupanca cp1(2, 2000, "Maria", 0.01);
    ContaCorrente cc2(3, 500, "Pedro", 100);
    
    banco.adicionarConta(&cc1);
    banco.adicionarConta(&cp1);
    banco.adicionarConta(&cc2);
    
    cc1.sacar(200);
    cc1.depositar(300);
    
    cp1.sacar(500);
    cp1.depositar(1000);
    banco.listarContas();
}




/*A primeira mensagem exibida é "Conta criada com sucesso", que é resultado da execução do construtor da classe Conta. 
As próximas três linhas exibem o número, titular e saldo da conta recém-criada. Essas mensagens são geradas para cada uma das três contas criadas na função main.

Em seguida, a função main realiza diversas operações bancárias. A primeira operação é um saque de 200 reais da conta cc1. 
Isso faz com que a mensagem "Saque realizado com sucesso" seja exibida, seguida do novo saldo da conta, que agora é de 800 reais.

Depois, um depósito de 300 reais é realizado na mesma conta, gerando a mensagem "Depósito realizado com sucesso" 
e mostrando o novo saldo de 1100 reais.

Em seguida, é feita uma tentativa de sacar 500 reais da conta cp1. 
Como o saldo da conta é 2000 reais e o saque é de 500 reais, a operação é realizada com sucesso,

Finalmente, um depósito de 1000 reais é feito na conta cp1, gerando novamente a mensagem "Depósito realizado com sucesso" 
e exibindo o novo saldo da conta, que agora é de 2500 reais.

Por fim, a função listarContas() do objeto banco é chamada, exibindo as informações de todas as contas adicionadas ao banco. 
Cada conta é listada com o seu número, titular e saldo atual.

*/


/* O programa está gerando memory leak 
porque as contas criadas são adicionadas ao vetor contas do objeto Banco, 
mas nunca são removidas de lá. O destrutor do objeto Banco apenas deleta os ponteiros, 
mas não libera a memória alocada para o objeto. Para corrigir isso, 
é necessário adicionar uma função que libere a memória das contas 
quando elas não forem mais necessárias, antes de deletar os ponteiros no destrutor.
*/