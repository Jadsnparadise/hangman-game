#include <iostream>
#include <vector>
using namespace std;

class Forca {
	public:
enum Dificuldade{
	FACIL, MEDIO, DIFICIL
};

private:
	vector<string> m_palavras_faceis; 

	vector<string> m_palavras_medias;

	vector<string> m_palavras_dificeis;

	vector<string> m_palpites_jogados;

	string m_palavra_progresso;

	string m_arquivo_scores; 

	string m_arquivo_palavras;

	string nome_jogador;

	Dificuldade m_dificuldade = Dificuldade::FACIL;

	string m_palavra_atual;

	vector<string> m_palavras_jogadas;

	int m_tentativas_restantes = 6; 

	int pontuacao = 0;

public:

	bool ganhou = false;

	Forca( string palavras, string scores );//feito

	pair<bool, string> eh_valido(string palavras, string scores);//feito

	void carrega_palavras(string arquivoPalavras);//feito

	void carrega_scores(string arquivoScores);//feito

	void atualiza_scores(string arquivoScores);//feito

	void set_dificuldade(Dificuldade d);//feito

	void proxima_palavra();//feito

	string get_palavra_atual();//feito

	string get_m_palavra_progresso();//feito

	bool palpite(std::string palpite);//feito

	void mensagem_startGame();//feito

	void mensagem_achou_letra();//feito

	void mensagem_nao_achou_letra();//feito

	void mensagem_pos_jogo();//feito

	void mensagem_ganhou();//feito

	bool game_over();//feito

	void boneco_progresso();

	void mensagem_game_over();//feito

	void set_tentativas_restantes(int tentativas);//feito

	int get_tentativas_restantes();//feito

	void set_nome_jogador(string nome);//feito

	string get_nome_jogador();//feito

	void set_pontuacao(int pontos);//feito

	int get_pontuacao();//feito

};
