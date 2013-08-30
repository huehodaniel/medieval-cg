/*!
 * \file
 *
 * Neste arquivo sao definidas as funcoes utilizadas para logica do jogo, por exemplo, disparo dos tiros,
 * deteccao de colisoes, etc.
 *
 */

#ifndef LOGICA_H
#define LOGICA_H

typedef enum _muralhaEstado { M0 = 0, M20, M40, M60, M80, M100 } muralhaEstado;

typedef enum _estadoJogador { PERDEU, JOGANDO, VENCEU, MORREU } estadoJogador;

typedef struct _projetil {
    float x;
    float y;
    float z;
    float ang;
} projetil;

typedef struct _force {
    float val;
} force;

typedef struct _plInfo {
    projetil p;
    force f;
	muralhaEstado* e;
	estadoJogador j;
	int pnt;
} plInfo;

plInfo getinfo_p1();

plInfo getinfo_p2();

/*!
 * \brief Funcao para inicializacao dos parametros utilizados na logica.
 *
 * \return void
 */
void initLogica();

/*!
 * \brief Funcao para atualizacao do angulo do projetil quando eh disparado.
 *
 * \param p Projetil disparado.
 *
 * \return void
 */
void updateByAngle(projetil* p);

/*!
 * \brief Funcao para verificar colisao com a muralha do jogador 1.
 *
 * \param p Projetil disparado.
 *
 * \return void
 */
void check_colision_p1(projetil p);

/*!
 * \brief Funcao para verificar colisao com a muralha do jogador 2.
 *
 * \param p Projetil disparado.
 *
 * \return void
 */
void check_colision_p2(projetil p);

/*!
 * \brief Funcao iniciar o disparo do canhao do jogador 1
 *
 * \param speed Velocidade do tiro.
 *
 * \return void
 */
void shoot_p1(int speed);

/*!
 * \brief Funcao para iniciar o incremento da forca do tiro do jogador 1
 *
 * \param inc Incremento da forca.
 *
 * \return void
 */
void force_p1(int inc);

/*!
 * \brief Funcao para finalizar o incremento da forca do tiro do jogador 1
 *
 * \param ang Angulo de disparo
 *
 * \return void
 */
void end_force_p1(float ang);

/*!
 * \brief Funcao iniciar o disparo do canhao do jogador 2
 *
 * \param speed Velocidade do tiro.
 *
 * \return void
 */
void shoot_p2(int speed);

/*!
 * \brief Funcao para iniciar o incremento da forca do tiro do jogador 2
 *
 * \param inc Incremento da forca.
 *
 * \return void
 */
void force_p2(int inc);

/*!
 * \brief Funcao para finalizar o incremento da forca do tiro do jogador 2
 *
 * \param ang Angulo de disparo
 *
 * \return void
 */
void end_force_p2(float ang);

#endif //LOGICA_H
