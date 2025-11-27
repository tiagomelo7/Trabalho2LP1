#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

class Produto {
public:
    string nome;
    string categoria;
    double preco;
    int estoque;

    Produto(string n, string c, double p, int e)
        :nome(n),categoria(c),preco(p),estoque(e){}

    void exibir() const {
        cout<<nome << " Categoria: " << categoria
             << "  Preço: R$ "<< preco
            << "  Estoque: "<< estoque;
    }
};
Produto* buscarProduto(vector<Produto>& produtos, const string& nome) {
    for (auto& p : produtos)
        if (p.nome == nome)
            return &p;
    return nullptr;
}
void listarPorCategoria(const vector<Produto>& produtos,const string& categoria) {
    cout<< "\nprodutos da categoria '" << categoria << "':\n";
    for (const auto& p : produtos)
        if (p.categoria ==categoria)
            p.exibir();
}
double calcularValorTotal(const vector<Produto>& produtos) {
    double total = 0;
    for (const auto& p : produtos)
        total += p.preco * p.estoque;
    return total;
}
void registrarVenda(vector<Produto>& produtos,
                    list<string>& historico,
                    const string& nome){
    Produto* p = buscarProduto(produtos, nome);
if (!p) {
        cout << "Produto não encontrado\n";
        return;
    }
 if (p->estoque <= 0) {
        cout << "Estoque insuficient\n";
        return;
    }
    p->estoque--;
    historico.push_back(nome);

    cout << "Venda registrada: " << nome;
}

int main(){
    vector<Produto> produtos;
    set<string> categorias;
    map<string, int> contagemPorCategoria;
    map<string, double> valorPorCategoria;
    list<string> historicoVendas;


    produtos.push_back(Produto ("Notebook","Eletronicos", 3500, 10));
    produtos.push_back(Produto ("Mouse","Eletronicos", 80, 50));
    produtos.push_back(Produto("Camisa","Vestuário", 120, 20));
    produtos.push_back(Produto("Tenis","Vestuário", 300, 15));
    produtos.push_back(Produto("Cafe","Alimentos", 15, 100));

    for (const auto& p : produtos) {
        categorias.insert(p.categoria);
        contagemPorCategoria[p.categoria]++;
        valorPorCategoria[p.categoria] += p.preco * p.estoque;
    }
    cout << "\n BUSCA DE PRODUTO\n";
    Produto* achado = buscarProduto(produtos, "Mouse");
    if(achado)
        achado->exibir();

    listarPorCategoria(produtos, "Vestuário");

    cout << "\nValor total do inventário: R$ "
         << calcularValorTotal(produtos) << endl;

    cout << "\n REGISTRANDO VENDAS\n";
    registrarVenda(produtos, historicoVendas, "Notebook");
    registrarVenda(produtos, historicoVendas, "Cafe");
    registrarVenda(produtos, historicoVendas, "Cafe");

    cout << "\nHistorico de vendas:\n";
    for (const auto& nome : historicoVendas)
        cout << "- " << nome;
    cout << "\nCATEGORIAS \n";
    for (const auto& c : categorias)
        cout << "- " << c;
    cout << "\nCONTAGEM POR CATEGORIA\n";
    for (const auto& par : contagemPorCategoria)
        cout << par.first << ": " << par.second << " produtos\n";
    cout << "\nVALOR POR CATEGORIA\n";
    for (const auto& par : valorPorCategoria)
        cout << par.first << ": R$ " << par.second; 

    return 0;
}
