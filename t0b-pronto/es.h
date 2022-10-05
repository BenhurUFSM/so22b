#ifndef ES_H
#define ES_H

// controlador de dispositivos de entrada e saida

#include <stdbool.h>
#include "err.h"

typedef struct es_t es_t; // declara o tipo como sendo uma estrutura opaca

// tipos de acesso que se pode fazer a um dispositivo
typedef enum { leitura, escrita } acesso_t;

// tipos de ponteiros de funções que um dispositivo deve implementar para
//   poder ser controlado pelo controlador de E/S
//   todas recebem como primeiros argumentos um ponteiro que identifica o
//   controlador desse dispositivo (o equivalente à controladora de hw)
//   e um inteiro que identifica o dispositivo entre os possivelmente vários
//   desse controlador. Esses valores são fornecidos quando o dispositivo é
//   registrado.
typedef err_t (*f_le_t)(void *contr, int id, int *endereco);
typedef err_t (*f_escr_t)(void *contr, int id, int valor);
typedef bool (*f_pronto_t)(void *contr, int id, acesso_t tipo_de_acesso);

// aloca e inicializa um controlador de E/S
// retorna NULL em caso de erro
es_t *es_cria(void);

// libera os recursos ocupados pelo controlador
void es_destroi(es_t *self);

// registra um dispositivo, identificado com o valor 'dispositivo', e que
//   será acessado através das funções apontadas pelos ponteiros 'f_le',
//   'f_escr' e 'f_pronto'
// se 'f_le' ou 'f_escr' for NULL, considera-se que a operação correspondente
//   é inválida; se 'f_pronto' for NULL, considera-se que está sempre pronto.
// retorna false se não foi possível registrar
bool es_registra_dispositivo(es_t *self, int dispositivo,
                             void *contr, int id,
                             f_le_t f_le, f_escr_t f_escr, f_pronto_t f_pronto);

// lê um inteiro de um dispositivo
// retorna ERR_OK se bem sucedido, ou
//   ERR_END_INV se dispositivo desconhecido
//   ERR_OP_INV se operação inválida
//   ERR_OCUP se dispositivo não estiver disponível
// a identificação do dispositivo é a que foi registrada, ou pode ser um
//   id virtual (>=100), que disponibiliza a prontidão de um dispositivo:
//   - lendo de um id>=100, se está lendo o estado de prontidão (1=pronto)
//     para leitura do dispositivo id-100
//   - lendo de um id>=200, se está lendo o estado de prontidão para escrita
//     do dispositivo id-200
//   (gambiarras acontecem...)
err_t es_le(es_t *self, int dispositivo, int *pvalor);

// escreve um inteiro em um dispositivo
// retorna ERR_OK se bem sucedido, ou
//   ERR_END_INV se dispositivo desconhecido
//   ERR_OP_INV se operação inválida
//   ERR_OCUP se dispositivo não estiver disponível ou pronto
err_t es_escreve(es_t *self, int dispositivo, int valor);

// retorna true se for possível realizar o acesso indicado
bool es_pronto(es_t *self, int dispositivo, acesso_t tipo_de_acesso);
#endif // ES_H
