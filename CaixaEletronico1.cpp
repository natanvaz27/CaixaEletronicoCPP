#include <iostream>
#include <stdlib.h>
#include <climits>
using namespace std;
const int n = 7;

//Vetor atribuindo as 7 notas dispon�veis no caixa eletr�nico
const int notas_tipo[n] = {100, 50, 20, 10, 5, 2, 1};

//Estrutura com vetor de 7 elementos
struct Notas{
int notas[n] = {0, 0, 0, 0, 0, 0, 0};
};


//----------------------FUN��ES----------------------------
void menu_cliente();
void conf_notas(Notas &estq);
void nova_opr();
void Ent_depst(Notas &estq, int &balanco);
void conf_saque(Notas &estq, int balanco, int saque);
void Ent_saque(Notas &estq, int saque);
void Saida_balanco(int balanco);
void cadastrar_admin(Notas &estq);
void menu_admin(Notas &estq);
void bal_caixa(Notas &estq);
void depst_caixa(Notas &estq);
void saida_depst_caixa(Notas &estq);
void validacao_entr_dados (int &var, string str, string invalid);


//FUN��O PRINCIPAL
int main(){
setlocale (LC_ALL, "Portuguese");

Notas estq;

int op, depst, saque;
int balanco = 0;

    do{
    //INICIO DO PROGRAMA
    cout << "Bem vindo!" << endl;
    conf_notas(estq);
    menu_cliente();
    validacao_entr_dados(op, "\nPor favor, escolha uma op��o: ", "Op��o inv�lida, tente novamente");

    //VERIFICA OP��ES
    switch(op){
    case 1:
        //VERIFICA QUANTIA
        Saida_balanco(balanco);
        nova_opr();
        break;

        //VERIFICA DEPOSITO
    case 2:
        Ent_depst(estq, balanco);
        Saida_balanco(balanco);
        nova_opr();
        break;

         //VERIFICA SAQUE
    case 3:
        do{
        validacao_entr_dados(saque, "\nDigite o valor que voc� deseja sacar: ", "Op��o inv�lida, tente novamente");
        conf_saque(estq, balanco, saque);

        }while(saque<0 || saque>balanco);
            balanco-=saque;
            Saida_balanco(balanco);
            nova_opr();
            break;

            //VERIFICA ACESSO ADMIN
    case 4:
        cadastrar_admin(estq);
        nova_opr();

    default:
        if(op<1 || op>5){
            cout << "Op��o inv�lida. Por favor digite novamente." << endl;
            break;
        }
    }

    }while(op!=5);
}


//----FUN��ES----

//1� FUN��O - Menu cliente, imprime as op��es que o cliente possui
void menu_cliente(){
    cout << "\n----------MENU----------";
    cout << "\n|1.Checar balan�o      |";
    cout << "\n|2.Deposito            |";
    cout << "\n|3.Saque               |";
    cout << "\n|4.Login Admin         |";
    cout << "\n|5.Sair                |";
    cout << "\n------------------------";
}

//2� FUN��O - Confere notas, validando se falta notas dentro do caixa
void conf_notas(Notas &estq){
    for(int i=0;i<n;i++){
        if(estq.notas[i]==0)
            cout << "\nPe�a para um administrador inserir mais notas de $" << notas_tipo[i];
    }
}

//3� FUN��O - Verifica��o com do-while (main) se o usu�rio deseja continuar ou n�o a execu��o
void nova_opr(){
char opcao;
    cout << "\nDigite S se quiser fazer mais uma opera��o? ";
    cin >> opcao;

    if(opcao=='S' || opcao=='s'){
        system ("CLS");
    }
    else
        exit(0);
}

//4� FUN��O - Usu�rio informa qual o valor que deseja depositar
void Ent_depst(Notas &estq, int &balanco){
int aux;
    for (int i=0; i<n; i++){
        do{
        cout << "Voc� quer depositar quantas notas de $" << notas_tipo[i] << ": ";
        cin >> aux;

            if(aux<0){
                cout << "Valor inv�lido. Digite novamente.\n" << endl;
            }
        }while(aux<0);
        estq.notas[i]+=aux;
        balanco+=(aux*notas_tipo[i]);
    }
    for(int i=0;i<n;i++){
        cout << "\nNotas total de " << notas_tipo[i] << ": " << estq.notas[i];
    }
}

//5� FUN��O - valida se o usu�rio pode sacar o n�o (evitando fraudes)
void conf_saque(Notas &estq, int balanco, int saque){
    if(saque<=0){
        cout << "Valor inv�lido. Digite novamente." << endl;
    }else if(saque>balanco){
        cout << "Voc� n�o possui saldo suficiente. O m�ximo que voc� pode retirar � $" << balanco << endl;
    }else if (balanco<100){
        cout << "Voc� tem menos de R$100, por favor deposite mais" << endl;
    }
    else
        Ent_saque(estq, saque);
}

//6� FUN��O - Imprime a quantia na conta do cliente
void Ent_saque(Notas &estq, int saque){
int aux;

//La�o de repeti��o atrav�s do c�lculo distribui��o �tima
    for (int i=0; i<n; i++){
    if(estq.notas[i]>0){
        aux = saque/notas_tipo[i];
        saque = saque%notas_tipo[i];
        estq.notas[i]-=aux;

        //Se a nota for menor que 0,
            for(int e=0;e<aux;e++){
            if(estq.notas[i]<0){
                estq.notas[i]++;
                saque+=notas_tipo[i];
            }
            }
    }
    }
    for(int i=0;i<n;i++){
        cout << "\nNotas total de " << notas_tipo[i] << ": " << estq.notas[i];
    }
}

//7� FUN��O: Imprime a quantia na conta do cliente
void Saida_balanco(int balanco){
    cout << "\nSeu balan�o atual �: $" << balanco;
}

//8� FUN��O: faz o login do admin para ter acesso ao gerenciamento do caixa
void cadastrar_admin(Notas &estq){
string login, senha;

    do{
    cout << "\nCADASTRO: \nLOGIN: ";
    cin >> login;
    cout << "SENHA: ";
    cin >> senha;

    if(login=="AdminSovietico" && senha=="******"){
        menu_admin(estq);
        break;
    }
    cout << "Login ou senha incorreta. Digite novamente." << endl;
    }while(login!="AdminSovietico" && senha!="******");
}

//9� FUN��O: admin tem acesso as op��es que deseja realizar
void menu_admin(Notas &estq){
int op;

    do{

    cout << "Bem vindo!" << endl;
    cout << "\n---------------MENU---------------";
    cout << "\n|1.Checar balan�o do caixa       |";
    cout << "\n|2.Depositar mais notas no caixa |";
    cout << "\n|3.Sair                          |";
    cout << "\n----------------------------------";
    cout << "\nPor favor, escolha uma op��o: ";
    cin >> op;

    switch(op){
        case 1:
            bal_caixa(estq);
            nova_opr();
            break;

        case 2:
            depst_caixa(estq);
            nova_opr();
            break;

        default:
        if(op<1 || op>3){
            cout << "Op��o inv�lida. Por favor digite novamente." << endl;
            break;
        }

    }
    }while(op!=3);
}

//10� fun��o: realiza o calculo do balan�o total do caixa (admin)
void bal_caixa(Notas &estq){
int balanco=0;
    for (int i=0; i<n; i++){
        balanco+=(estq.notas[i]*notas_tipo[i]);
    }
    cout << "\nO bala�o atual do caixa �: " << balanco << endl;

    for(int i=0;i<n;i++){
        cout << "\nNotas total de " << notas_tipo[i] << ": " << estq.notas[i];
    }
}

//11� fun��o: realiza o deposito de notas no caixa (admin)
void depst_caixa(Notas &estq){
int aux;
    for (int i=0; i<n; i++){
        do{
        cout << "Voc� quer depositar quantas notas de $" << notas_tipo[i] << ": ";
        cin >> aux;

            if(aux<0){
                cout << "Valor inv�lido. Digite novamente." << endl;
            }
        }while(aux<0);
        estq.notas[i]+=aux;
    }
    cout << "\n\n";
    saida_depst_caixa(estq);
}

//12� fun��o: informa��o de quantas notas h� no caixa
void saida_depst_caixa(Notas &estq){
    for (int i=0; i<n; i++){
        cout << "TOTAL DE NOTAS DISPONIVEIS DE R$" << notas_tipo[i] << ": " << estq.notas[i] << endl;
    }
}

//13� fun��o: valida se o usu�rio digita o esperado
void validacao_entr_dados (int &var, string str, string invalid){
bool valid = false;
while(!valid){
    cout << str;
    cin >> var;
    if (cin.fail())
    {
        cout << invalid;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    } else
    valid = true;
}
}
