#include <iostream>
#include <map>
#include <utility>


using namespace std;

typedef struct contas{
    string nomeconta;
    string senha;
    struct contas *proximo;

}contas;

typedef struct usuarios{

    struct contas *contas;

}usuarios;

struct contas *primeiro, *atual, *aux, *novaconta;

int chave(const int * const);
inline bool validaCPF(const int * const);
void imprimir();
void inserirconta(string);
void buscar(int);

int main()
{
    int i, opcao;
    int posicao;
    string stringcpf;
    int cpf[11];


    string nomeconta;
    map<int, usuarios> lista;


    do{

        cout<< "Insira um CPF: ";
        cin >> stringcpf;
        for(int i=0; i < 11; i++){
            if(stringcpf[i] < '0' || stringcpf[i] > '9' || stringcpf.length()>11){ //Validando a entrada de dados
                cout << "ENTRADA INVÁLIDA. Digite Novamente.\n" << endl;
                cin>>stringcpf;
                i=-1;
            }
        }
        for(int i = 0; i < 11; i++){
            cpf[i] = stringcpf[i] - '0'; //Convertendo char para valor absoluto segundo tabela ASCII e passando para array de inteiros//
        }
        if(!validaCPF(cpf)){
            cout<<"CPF INVALIDO!!!\n";
            break;
        }else{
            cout<<"CPF válido.\n";
        }

        cout<<"1 - Cadastrar conta:\n"
        <<"2 - Buscar cpf:\n";
        cin>>opcao;


        switch(opcao){
            case 1:
                cout<< "Insira um nomeconta: ";
                cin>>nomeconta;


                posicao=chave(cpf);

                if(lista.find(posicao)==lista.end()){
                    usuarios novo;
                    novo.contas=NULL;

                    lista[posicao]=novo;
                }

                primeiro=(contas*)malloc(sizeof(contas));
                if(lista[posicao].contas==NULL){
                    lista[posicao].contas=(contas*)malloc(sizeof(contas));
                }
                primeiro=lista[posicao].contas;

                inserirconta(nomeconta);

                lista[posicao].contas=primeiro;
                cin.clear();
                break;


            case 2:

                posicao=chave(cpf);
                //cpf=chave(nomeconta);
                if(lista.find(posicao)!=lista.end()){
                    primeiro=lista[posicao].contas;
                    buscar(posicao);
                }else{
                    cout<< "\nCPF não encontrado!";
                }

        }

    }while(opcao!=3);

    return 0;
}

void inserirconta(string nomeconta){
    string senha;

    novaconta=(contas*)malloc(sizeof(contas));

    cout<<"Insira uma de senha: ";
    cin>>senha;



    novaconta->nomeconta=nomeconta;
    novaconta->senha=senha;
    atual = primeiro;
    aux=atual;

    if(atual->nomeconta.length()==0){
        primeiro->nomeconta=nomeconta;
        primeiro->senha=senha;
        return;
    }

    while(atual!=NULL){



        if(novaconta->nomeconta.compare(atual->nomeconta) > 0 || novaconta->nomeconta.compare(atual->nomeconta)==0){
            aux=atual;
            if(atual->proximo==NULL){
                atual->proximo=novaconta;
                break;
            }
            atual=atual->proximo;


        }else if(novaconta->nomeconta.compare(atual->nomeconta)<0){
            if(atual==aux){
                novaconta->proximo=atual;
                primeiro=novaconta;
                break;
            }else{
                aux->proximo=novaconta;
                novaconta->proximo=atual;
                break;

            }
        }
    }
}


void buscar(int cpf){
  atual = primeiro;

  while(atual!=NULL){

      cout << "\nnomeconta: " << atual->nomeconta <<
      "\nsenha: " << atual->senha<<
      "\n";
      atual=atual->proximo;


  }

}

inline bool validaCPF(const int * const cpf)
{
    int digito1,
        digito2,
        temp = 0;

    /*Obtendo o primeiro digito verificador:

    Os 9 primeiros algarismos são multiplicados pela sequência 10, 9, 8, 7, 6, 5, 4, 3, 2
    (o primeiro por 10, o segundo por 9, e assim por diante);
    Em seguida, calcula-se o resto “r1″ da divisão da soma dos resultados das multiplicações por 11,
    e se o resto for zero ou 1, digito é zero, caso contrário digito = (11-r1) */
    for(int i = 0; i < 9; i++)
        temp += (cpf[i] * (10 - i));

    temp %= 11;

    if(temp < 2)
        digito1 = 0;
    else
        digito1 = 11 - temp;

    /*Obtendo o segundo digito verificador:

    O dígito2 é calculado pela mesma regra, porém inclui-se o primeiro digito verificador ao final
    da sequencia. Os 10 primeiros algarismos são multiplicados pela sequencia 11, 10, 9, ... etc...
    (o primeiro por 11, o segundo por 10, e assim por diante);
    procedendo da mesma maneira do primeiro digito*/

    temp = 0;
    for(int i = 0; i < 10; i++)
        temp += (cpf[i] * (11 - i));

    temp %= 11;

    if(temp < 2)
        digito2 = 0;
    else
        digito2 = 11 - temp;

    /* Se os digitos verificadores obtidos forem iguais aos informados pelo usuário,
       então o CPF é válido */

    if(digito1 == cpf[9] && digito2 == cpf[10])
        return true;
    else
        return false;
}

int chave(const int * const cpf){
    int temp=0;
    for(int i = 0; i < 9; i++)
        temp += (cpf[i] * (10 - i));

    return temp;
}
