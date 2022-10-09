#include "Forca.hpp"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

//-------- Construtor --------
Forca::Forca( string palavras, string scores ){
	m_arquivo_palavras = palavras;
	m_arquivo_palavras = scores;
	m_tentativas_restantes = 6;
}
//-------- Verifica se o arquivo de palavras é válido --------
pair<bool, string> Forca::eh_valido(string arquivoPalavras, string arquivoScores){
	bool letraValida;
	string palavra;
	ifstream arqPalavras;
	pair <bool,string> eh_valido;
	arqPalavras.open(arquivoPalavras,ios::in);
	
	for(int i = 0; getline(arqPalavras, palavra); i++){
		if(palavra.size() < 4){
			eh_valido = make_pair(false,"Há uma palavra com menos de 4 caracteres");
		break;
		}
		
		for(int j = 0; j < palavra.size(); j++){
			if(palavra[j] >= 'a' && palavra[j] <= 'z' || palavra[j] >= 'A' && palavra[j] <= 'Z' || palavra[j] == '-'){
				letraValida = true;
				
			}else{
				
				letraValida = false;
				eh_valido = make_pair(letraValida,"O arquivo com as palavras contém caracteres inválidos :(");
				break;
			}
		}
		
		if(letraValida == false){
			break;
			
		}else{
			eh_valido = make_pair(letraValida,"");
		}
	}
	
	arqPalavras.close();
	return eh_valido;
}

//-------- seta a Dificuldade do Jogo --------

void Forca::set_dificuldade(Dificuldade mode){
	m_dificuldade = mode;
}

//-------- Carrega os vetores de palavras separadas pela dificuldade --------
void Forca::carrega_palavras(string arquivoPalavras){
	ifstream arqPalavras;
	string palavra;

	arqPalavras.open(arquivoPalavras);
		
	for(int i = 0; getline(arqPalavras, palavra); i++){
		if(palavra.size() <= 6){
			
			m_palavras_faceis.push_back(palavra);
			
		}else if(palavra.size() > 6 && palavra.size() <= 8){
			
			m_palavras_medias.push_back(palavra);

		}else if(palavra.size() > 8){
			
			m_palavras_dificeis.push_back(palavra);
		}
	}		
	arqPalavras.close();
}

//------------ESCOLHE A PALAVRA DA RODADA DEPENDENDO DA DIFILCUDADE---------
void Forca::proxima_palavra(){
	int mode = m_dificuldade;
	int indicePalavra;
	string linhas = "";
	int consoantesRestantes = 0, vogaisRestantes = 0;
	bool achouletra;
	switch(mode){

		//------------CASO FOR NO MODO FÁCIL--------------
		case 0:
			indicePalavra = (int)rand() %m_palavras_faceis.size();
			m_palavra_atual = m_palavras_faceis[indicePalavra] ;

			m_palavras_jogadas.push_back(m_palavra_atual);
			m_palavras_faceis.erase(m_palavras_faceis.begin()+indicePalavra);
			
			consoantesRestantes = (int)m_palavra_atual.size()/5;
			
			//cout << "\nPalavra da rodada = "<< m_palavra_atual<<endl;
			for(int i = 0; i < m_palavra_atual.size();i++){
				string consoantes = "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ";
				achouletra = false;
				for(int j = 0; j < consoantes.size(); j++){
					if(to_string(m_palavra_atual[i]).compare(to_string(consoantes[j])) == 0 && consoantesRestantes > 0 ){
						linhas += consoantes[j];
						consoantesRestantes--;
						achouletra = true;
					}
				}
				if(achouletra == false){
					linhas += "_";
				}
			}
			m_palavra_progresso = linhas;
			cout << linhas <<"\n"<< endl; 
			
		break;

		//-----------CASO FOR NO MODO MÉDIO-----------
		case 1:
			indicePalavra = (int)rand() %m_palavras_medias.size();
			m_palavra_atual = m_palavras_medias[indicePalavra];
			
			m_palavras_jogadas.push_back(m_palavra_atual);
			m_palavras_medias.erase(m_palavras_medias.begin()+indicePalavra);
			
			vogaisRestantes = (int)m_palavra_atual.size()/5;
			
			//cout << "\nPalavra da rodada = "<< m_palavra_atual<<endl;
			
			for(int i = 0; i < m_palavra_atual.size();i++){
				string vogais = "aeiouAEIOU";
				achouletra = false;
				for(int j = 0; j < vogais.size(); j++){
					if(to_string(m_palavra_atual[i]).compare(to_string(vogais[j])) == 0 && vogaisRestantes > 0 ){
						linhas += vogais[j];
						vogaisRestantes--;
						achouletra = true;
					}
				}
				if(achouletra == false){
					linhas += "_";
				}
			}

			m_palavra_progresso = linhas;
			cout << linhas <<"\n"<< endl; 
		break;

		//-----------CASO FOR NO MODO DIFÍCIL-----------
		case 2:
			indicePalavra = (int)rand() %m_palavras_dificeis.size();
			m_palavra_atual = m_palavras_dificeis[indicePalavra] ;

			m_palavras_jogadas.push_back(m_palavra_atual);
			m_palavras_faceis.erase(m_palavras_dificeis.begin()+indicePalavra);
			
			m_palavra_progresso = linhas;
		break;
	}
		
}

//-------------Retorna a Palavra da rodada Atual------------
string Forca::get_palavra_atual(){
	return m_palavra_atual;
}

//------------Imprime uma mensagem como cabeçalho para a rodada--------
void Forca:: mensagem_startGame(){
	string mode;
	if(m_dificuldade == 0){
		mode = "Fácil";
	}else if(m_dificuldade == 1){
		mode = "Médio";
	}else{
		mode = "Díficil";
	}
	cout<< "\nJogo no nível "<<mode <<", será que você conhece essa palavra? O.O\n"<< endl;
}

//-------confere se acertou o palpite ou não, altera o progresso da palavra, os pontos e as tentativas restantes------
bool Forca::palpite(string palpite){
	int contLetraIgual = 0;
	char letrPalpite[2] = {char(palpite[0])};
	char letraDaIteracao[2];
	
	if(palpite.compare(m_palavra_atual) == 0){
		pontuacao += m_palavra_atual.size() + 2;
		ganhou = true;
		return true;
	}else{
		for(int i = 0; i < m_palavra_atual.size(); i++){
			letraDaIteracao[0] = m_palavra_atual[i];
			if(strcmp(letraDaIteracao,letrPalpite) == 0 && palpite.size()==1){
				m_palavra_progresso = m_palavra_progresso.replace(i,1,palpite);
				contLetraIgual++;
			}
		}
		if(contLetraIgual == 0){	set_tentativas_restantes(get_tentativas_restantes()-1);
			mensagem_nao_achou_letra();
			pontuacao--;
			return false;
		}else if(m_palavra_atual == m_palavra_progresso){
			pontuacao++;
			if(m_tentativas_restantes == 6){
				pontuacao+=2;
			}
			ganhou = true;
			return true;
		}
		
		else{
			pontuacao++;
			mensagem_achou_letra();
			return true;
		}
	}
}

//--------Seta as tentativas restantes do jogador---------
void Forca::set_tentativas_restantes(int tentativas){
	m_tentativas_restantes = tentativas;
}

//---------Retorna as tentivas restantes do jogador--------
int Forca::get_tentativas_restantes(){
	return m_tentativas_restantes;
}

//---------Retorna o progresso da palavra ex:"_a_a" para casa-------
string Forca::get_m_palavra_progresso(){
	return m_palavra_progresso;
}

//---------Seta o nome do jogador que jogou a partida-------
void Forca::set_nome_jogador(string nome){
	nome_jogador = nome;
}

//---------Retorna o nome do jogafor que jogou a partida-------
string Forca::get_nome_jogador(){
	return nome_jogador;
}

//---------Mensagem para caso tenha acertado o palpite--------
void Forca::mensagem_achou_letra(){
	cout << endl;
	cout << "Eita!! o.o vc acertou bora para a próxima letra! Então qual vai ser?"<<endl;
	cout << endl;
}

//---------Mensagem para caso não tenha acertado o palpite--------
void Forca::mensagem_nao_achou_letra(){
	cout << endl;
	cout << "vish!! D: tu errou boy, mas vida que segue bora pra próxima letra, qual vai ser?"<< endl;
	cout << endl;
}

//---------Modifica os pontos-----------
void Forca::set_pontuacao(int pontos){
	pontuacao = pontos;
}

//---------retorna os pontos atuais-----------
int Forca::get_pontuacao(){
	return pontuacao;
}

//--------pergunta se quer jogar novamente----------
void Forca::mensagem_pos_jogo(){
	cout <<"     >você quer jogar novamente? :P"<<endl;
	cout << endl;
	cout <<"      1 - Sim :D (mesma dificuldade)\n" << endl;
	cout << endl;
	cout <<"      2 - Não D: (encerra o jogo) \n" << endl;
	cout << endl;
}

//---------imprime mensagem para caso acertou a palavra-----------
void Forca::mensagem_ganhou(){
	cout<<"\n     >PARABÉNS VOCÊ ACERTOU A PALAVRA!! :D"<<endl;
	cout << endl;
	cout <<"      >A palavra era "<< m_palavra_atual<<endl;
	cout << endl;
}

//---------atualiza o arquivo scores com os dados da partida que se encerrou-----------
void Forca::atualiza_scores(string arquivoScores){
	ofstream arqScores;
	string mode;
	
	if(m_dificuldade == 0){
		mode = "Fácil";
	}else if(m_dificuldade == 1){
		mode = "Médio";
	}else{
		mode = "Díficil";
	}
	
	string palavras;
	
	for(int i = 0; i < m_palavras_jogadas.size(); i++){
		if(i == m_palavras_jogadas.size()-1){
			palavras += m_palavras_jogadas[i]+"; ";
		}else{
			palavras += m_palavras_jogadas[i]+", ";
		}
	}
	
	arqScores.open(arquivoScores,ios::app);
	arqScores << mode<<"; "<< nome_jogador<<"; " << palavras<<pontuacao<<endl;

	arqScores.close();
}

//---------Retorna se foi game over ou não-----------
bool Forca::game_over(){
	if(m_tentativas_restantes == 0){
		return true;
	}else{
		return false;
	}
}

//---------Imprime mensagem de game over-----------
void Forca::mensagem_game_over(){
	cout<<endl;
	cout << "Pontos: "<<pontuacao<<endl;
	cout<<endl;
	cout<< "VISHHHH!! G-A-M-E   O-V-E-R"<<endl; 
	cout<< " O"<<endl;
	cout<< "/|\\"<<endl;
	cout<< "/ \\"<<endl;
	cout<<endl;
	cout<<"A palavra era "<<m_palavra_atual<<endl;
	cout<< "Espero que não desista tão facilmente!"<<endl;
	cout<<endl;
}

//---------Mostra a lista de scores anteriores-----------
void Forca::carrega_scores(string arquivoScores){
	ifstream arqScores;
	arqScores.open(arquivoScores,ios::in);
	string dados;
	cout << endl;
	cout << "============SCORES ANTERIORES============"<<endl;
	for(int i = 0; getline(arqScores, dados); i++){
		cout << dados<<endl;
	}
	cout << endl;
	cout << endl;
	cout <<"      1 - Voltar\n"<< endl;
}

//---------Progresso do boneco baseado nas tentativas restantes-----------
void Forca::boneco_progresso(){
	if(get_tentativas_restantes() == 5){
		cout<<endl;
		cout << " O"<<endl;
	}else if(get_tentativas_restantes() == 4){
		cout<<endl<<endl;
		cout << " O"<<endl;
		cout << " |"<<endl;
	}else if(get_tentativas_restantes() == 3){
		cout<<endl<<endl;
		cout << " O"<<endl;
		cout << "/|"<<endl;
	}else if(get_tentativas_restantes() == 2){
		cout<<endl<<endl;
		cout << " O"<<endl;
		cout << "/|\\"<<endl;
	}else if(get_tentativas_restantes() == 1){
		cout<<endl<<endl;
		cout << " O"<<endl;
		cout << "/|\\"<<endl;
		cout << "/"<<endl;
	}else if(get_tentativas_restantes() == 0){
		cout<<endl<<endl;
		cout << " O"<<endl;
		cout << "/|\\"<<endl;
		cout << "/ \\"<<endl;
	}
}