#ifndef _GROUP_H_
#define _GROUP_H_

typedef struct group Group;

/// @brief Cria um grupo vazio
/// @return 
Group *Group_Create();

/// @brief Destrói um grupo (é necessário passar como parâmetro a função de destruição dos itens internos)
/// @param g 
/// @param ContentDestroy_fn 
void Group_Destroy(Group *g, void (*ContentDestroy_fn)(void *));

/// @brief Adiciona um item qualquer no grupo selecionado
/// @param g 
/// @param content 
void groupPush(Group *g, void *content);

/// @brief Remove um item qualquer do grupo selecionado e o retorna
/// @param g 
/// @return 
void *groupPop(Group *g);

/// @brief Exibe os itens e informações do grupo selecionado
/// @param g 
/// @param ContentPrint_fn 
void groupDebugContent(Group *g, void (*ContentPrint_fn)(void *));

#endif