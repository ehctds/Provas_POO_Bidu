#include <iostream>
using namespace std;

class Produto { //classe abstrata com metodo virtual puro,seus atributos e métodos
protected: //protected para que as classes derivadas possam acessar
    string nome;
    float preco;
    int quantidade_estoque;

public:
    Produto(string n, float p, int q) {
        nome = n;
        preco = p;
        quantidade_estoque = q;
    }
    //gets e sets
    
    string get_nome() {
        return nome;
    }

    float get_preco() {
        return preco;
    }

    int get_quantidade_estoque() {
        return quantidade_estoque;
    }

    void set_nome(string n) {
        nome = n;
    }

    void set_preco(float p) {
        preco = p;
    }

    void set_quantidade_estoque(int q) {
        quantidade_estoque = q;
    }

    virtual void print_info() = 0; //metodo virtual puro, que obriga as classes a determinarem o que fazer
};

class Ferramenta : virtual public Produto { //classe ferramenta que herda de produto
protected: //protected para que as classes derivadas possam acessar
    string tipo_ferramenta;

public:
    Ferramenta(string n, float p, int q, string t) : Produto(n, p, q), tipo_ferramenta(t) {}

    //gets e sets
    string get_tipo_ferramenta() {
        return tipo_ferramenta;
    }

    void set_tipo_ferramenta(string t) {
        tipo_ferramenta = t;
    }

    void print_info() { //metodo print_info que imprime as informações da ferramenta tendo como base o método virtual puro da classe produto
        cout << "Nome: " << nome << endl;
        cout << "Preco: " << preco << endl;
        cout << "Quantidade em estoque: " << quantidade_estoque << endl;
        cout << "Tipo de ferramenta: " << tipo_ferramenta << endl;
    }
};

class Material : virtual public Produto { //classe material que herda de produto
protected: //protected para que as classes derivadas possam acessar
    string tipo_material;

public:
    Material(string n, float p, int q, string t) : Produto(n, p, q), tipo_material(t) {}

    //gets e sets
    string get_tipo_material() {
        return tipo_material;
    }

    void set_tipo_material(string t) {
        tipo_material = t;
    }

    void print_info() { //metodo print_info que imprime as informações do material tendo como base o método virtual puro da classe produto
        cout << "Nome: " << nome << endl;
        cout << "Preco: " << preco << endl;
        cout << "Quantidade em estoque: " << quantidade_estoque << endl;
        cout << "Tipo de material: " << tipo_material << endl;
    }
};

class FerramentaEletrica : public Ferramenta, public Material { //classe ferramenta eletrica que herda de ferramenta e material
public:
    FerramentaEletrica(string n, float p, int q, string t, string m) : Produto(n, p, q), Ferramenta(n, p, q, t), Material(n, p, q, m) {}

    void print_info() { //metodo print_info que imprime as informações da ferramenta eletrica tendo como base o método virtual puro evitando ambiguidade
        cout << "Nome: " << nome << endl;
        cout << "Preco: " << preco << endl;
        cout << "Quantidade em estoque: " << quantidade_estoque << endl;
        cout << "Tipo de ferramenta: " << tipo_ferramenta << endl;
        cout << "Tipo de material: " << tipo_material << endl;
    }
};

int main() {
    Produto* produtos[6]; //vetor de ponteiros para a classe produto

    //instanciando objetos das classes
    Ferramenta f1("Martelo", 19.99, 5, "Ferramenta de impacto");
    Ferramenta f2("Chave de fenda", 9.99, 10, "Ferramenta de aperto");
    Material m1("Prego", 0.99, 100, "Material de fixação");
    Material m2("Parafuso", 1.99, 100, "Material de fixação");
    FerramentaEletrica fe1("Furadeira", 199.99, 2, "Ferramenta de impacto", "Material de fixação");
    FerramentaEletrica fe2("Serra eletrica", 299.99, 1, "Ferramenta de corte", "Material de fixação");

    produtos[0] = &f1;
    produtos[1] = &f2;
    produtos[2] = &m1;
    produtos[3] = &m2;
    produtos[4] = &fe1;
    produtos[5] = &fe2;

    //imprimindo as informações dos objetos
    for (int i = 0; i < 6; i++) {
        produtos[i]->print_info();
        cout << endl;
    }

    return 0;
}
