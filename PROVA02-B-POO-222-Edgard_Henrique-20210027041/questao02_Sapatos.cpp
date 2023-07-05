#include <iostream>
using namespace std;

class produto{
    string nome;
    float preco;
    int quantidade_estoque;
public:
    static int total_produtos; //static para que seja compartilhado entre todas as instancias da classe
    produto(string n, float p, int q){
        nome = n;
        preco = p;
        quantidade_estoque = q;
        total_produtos++;
    }
    //gets e sets
    string get_nome(){
        return nome;
    }
    float get_preco(){
        return preco;
    }
    int get_quantidade_estoque(){
        return quantidade_estoque;
    }
    void set_nome(string n){
        nome = n;
    }
    void set_preco(float p){
        preco = p;
    }
    void set_quantidade_estoque(int q){
        quantidade_estoque = q;
    }
    static int get_total_produtos(){
        return total_produtos;
    }
    virtual void print_info() //metodo virtual de print_info para que as classes derivadas possam sobrescrever
    {
        cout << "Nome: " << nome << endl;
        cout << "Preco: " << preco << endl;
        cout << "Quantidade em estoque: " << quantidade_estoque << endl;
    }
};

class sapato: public produto{ //classe sapato que herda de produto
    string cor;
    int tamanho;
public:
    sapato(string n, float p, int q, string c, int t): produto(n,p,q), cor(c), tamanho(t) {}
    string get_cor(){
        return cor;
    }
    //gets e sets
    int get_tamanho(){
        return tamanho;
    }
    void set_cor(string c){
        cor = c;
    }
    void set_tamanho(int t){
        tamanho = t;
    }
    void print_info(){ //metodo print_info que imprime as informações do sapato tendo como base o método virtual de print_info da classe produto
        cout << endl;
        produto::print_info();
        cout << "Cor: " << cor << endl;
        cout << "Tamanho: " << tamanho << endl;
    }
};

class tenis:public sapato{ //classe tenis que herda de sapato
    string marca;
public:
    tenis(string n, float p, int q, string c, int t, string m): sapato(n,p,q,c,t), marca(m) {}
    
    //gets e sets
    string get_marca(){
        return marca;
    }
    void set_marca(string m){
        marca = m;
    }
    void print_info(){
        sapato::print_info();
        cout << "Marca: " << marca << endl;
    }
};
int produto::total_produtos = 0;

int main(){
    produto* produtos[3]; //vetor de ponteiros para a classe produto

    //instanciando objetos das classes sapato e tenis
    sapato s1("Sapato Social", 199.99, 5, "Preto", 42);
    tenis t1("Tênis Esportivo", 149.99, 10, "Branco", 41, "Nike");
    tenis t2("Tênis Casual", 129.99, 8, "Azul", 39, "Adidas");
    
    produtos[0] = &s1;
    produtos[1] = &t1;
    produtos[2] = &t2;

    //imprimindo as informações dos produtos
    for (int i = 0; i < 3; i++) {
        produtos[i]->print_info();
        cout << endl;
    }

    //imprimindo o total de produtos criados usando a variavel estatica total_produtos
    cout << "Total de produtos criados: " << produto::total_produtos << endl;

    return 0;
}
