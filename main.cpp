#include <iostream>
#include <fstream>
#include <string>
#include "Forca.hpp"

using namespace std;

void clear(){
  std::cout<< "\033[2J\033[1;1H";
	}

int main(int argc, char *argv[]) {
	srand (time(NULL));
	Forca forca("palavras.txt","scores.txt");

	cout << ">     Um momento... Lendo os arquivos de Palavras e de Scores :D " << endl;
	auto valido = forca.eh_valido("palavras.txt","scores.txt");
	forca.carrega_palavras("palavras.txt");

	if(valido.first == false){
		cout << "Error 666: " << valido.second << endl;
		exit(-1);
	}

	int tela = -1;
	int escolha;
	int dificuldade = 0;
	string palpite;
	cout << "===========================================" << endl;
	cout << "      Tudo certo com os arquivos :P" << endl;
	cout << "===========================================\n" << endl;

	cout << ">     Seja bem vindo ao Jogo da Forca! Espero que se divirta XD\n" << endl;
	
	while(true){
		forca.set_tentativas_restantes(6);	
		forca.ganhou = false;
		
		if(tela == -1){
		
			cout << 	"================= MENU ====================\n" << endl;
			cout <<"      1 - Iniciar Jogo\n" << endl;
			cout <<"      2 - Ver scores anteriores\n" << endl;
			cout <<"      3 - Sair\n" << endl;
			cout << "===========================================\n" << endl;
			cout << "      Por favor escolha uma das Opções\n" << endl;
			
		
			cout << "     >";
			cin >> escolha;
			tela = 0;
			clear();
			
		}
		if(escolha == 1 && tela == 0){
			
		//----------CASO ESCOLHA INICIAR JOGO-----------
			cout << 	"=========== MENU DE DIFICULDADES ===========\n" << endl;
			cout <<"      1 - Fácil :D\n" << endl;
			cout <<"      2 - Médio XD\n " << endl;
			cout <<"      3 - SEM PIEDADE >:)\n" << endl;
			cout << "===========================================\n" << endl;
			cout << "      Por favor escolha uma das Opções\n" << endl;
			cin >> dificuldade;
			
			
			//------ESCOLHA DE DIFICULDADE-------
			switch(dificuldade){
			
				case 1:	
					forca.set_dificuldade(forca.FACIL);
					tela = 1;
				break;

				case 2:
					forca.set_dificuldade(forca.MEDIO);
					tela = 1;
				break;

				case 3:
					forca.set_dificuldade(forca.DIFICIL);
					tela = 1;
				break;

				default:
					tela = 4;
				break;
			}		
		}
	
		if(tela == 1){
			clear();
			forca.mensagem_startGame();
			forca.proxima_palavra();
			
			while(forca.get_tentativas_restantes() != 0){
				forca.boneco_progresso();
				cout<< "\nPontos: "<<forca.get_pontuacao()<<endl;
				cout << "tentativas = "<<forca.get_tentativas_restantes()<<endl;
				cout<<"Palpite: ";
				cin >> palpite;
				forca.palpite(palpite);
				
				if(forca.ganhou == true){
					cout<< "\nPontos: "<<forca.get_pontuacao()<<endl;
					forca.mensagem_ganhou();
					tela = 5;
					break;
				}
				cout<<forca.get_m_palavra_progresso()<<endl;
			
			}
			if(forca.game_over() == true){
				forca.mensagem_game_over();
				tela = 5;
			}
		
		}
	
		//--------CASO ESCOLHA VER SCORES--------
		if(escolha == 2){
			cout<<endl;
			int opcao;
			forca.carrega_scores("scores.txt");
			cin >> opcao;
			if(opcao == 1){
				tela = -1;
				escolha = 1;
			}else{
				tela = 4;
				escolha = 4;
			}
		}
	
		//--------CASO ESCOLHA SAIR--------
		if(escolha == 3){
			cout << "     >Obrigado por Jogar, até a próxima\n     >Saindo...";
		exit(-1);
		}

		//--------CASO ESCOLHA UMA OPÇÃO INVÁLIDA--------
		if(escolha < 1 || escolha > 3 || tela == 4){
			cout << "     >Opção inválida, encerrando programa";
			exit(-1);
		}

		if(tela == 5){
			int escolhido;
			forca.mensagem_pos_jogo();
			cout<< "Escolha:";
			cin >> escolhido;
			
			if(escolhido == 1){
				cout << "\n      >E lá vamos nós de novo!!!";
				tela = escolhido;
				
			}else if(escolhido == 2){
				cout << "\nTudo bem então, por favor insira seu nome: "<<endl;
				string nome;
				cin >> nome;
				forca.set_nome_jogador(nome);
					cout << "     >Muito Obrigado "<<forca.get_nome_jogador()<< "! até a próxima! Encerrando programa...";
				forca.atualiza_scores("scores.txt");
					exit(-1);
			}else{
				tela = 4;
			}
		}
		clear();
	}
	return 0;
}