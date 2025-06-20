#include "minishell.h"
#include <string.h>
#include <stdio.h>

#define MAX_WIDTH 200
#define MAX_HEIGHT 50

typedef struct s_layout {
	int width;      // largeur totale nécessaire
	int center_x;   // position horizontale du centre du noeud
	int top_y;      // position verticale du noeud
} t_layout;

// 1) Calculer la taille (width) et centre (center_x) de chaque sous-arbre, sans dessiner
t_layout calc_layout(t_ast *node)
{
	t_layout layout = {0, 0, 0};
	if (!node)
		return layout;

	char label[64] = {0};
	if (node->type == PIPE)
		snprintf(label, sizeof(label), "PIPE");
	else if (node->type == AND)
		snprintf(label, sizeof(label), "&&");
	else if (node->type == OR)
		snprintf(label, sizeof(label), "||");
	else if (node->type == CMD)
	{
		if (node->command.args && node->command.args[0])
			snprintf(label, sizeof(label), "%s", node->command.args[0]);
		else
			snprintf(label, sizeof(label), "CMD");

		for (int i = 1; node->command.args && node->command.args[i]; i++) {
			strncat(label, " ", sizeof(label) - strlen(label) - 1);
			strncat(label, node->command.args[i], sizeof(label) - strlen(label) - 1);
		}
	}
	else
		snprintf(label, sizeof(label), "NODE");

	int label_len = strlen(label);
	int box_width = label_len + 4;

	if (node->type == PIPE || node->type == AND || node->type == OR)
	{
		t_layout left = calc_layout(node->pipe.left);
		t_layout right = calc_layout(node->pipe.right);
		int spacing = 6;

		// Largeur totale = somme des largeurs + espacement
		layout.width = left.width + right.width + spacing;
		if (layout.width < box_width)
			layout.width = box_width;

		// Centre au milieu de la largeur totale
		layout.center_x = layout.width / 2;
	}
	else
	{
		layout.width = box_width;
		layout.center_x = box_width / 2;
	}

	return layout;
}

void place_node(char canvas[MAX_HEIGHT][MAX_WIDTH], int x, int y, const char *label)
{
	int len = strlen(label);
	int box_width = len + 4;

	if (x < 2)
		x = 2;
	if (x + box_width >= MAX_WIDTH)
		x = MAX_WIDTH - box_width - 1;

	// Top border
	canvas[y][x] = '+';
	for (int i = 1; i < box_width - 1; i++)
		canvas[y][x + i] = '-';
	canvas[y][x + box_width - 1] = '+';

	// Label row
	canvas[y + 1][x] = '|';
	for (int i = 0; i < len; i++)
		canvas[y + 1][x + 2 + i] = label[i];  // correction ici (x + 2 + i au lieu de x + 2 + i - 1)
	canvas[y + 1][x + box_width - 1] = '|';

	// Fill spaces (au cas où)
	for (int i = 1; i < box_width - 1; i++)
		if (canvas[y + 1][x + i] == 0 || canvas[y + 1][x + i] == ' ')
			canvas[y + 1][x + i] = ' ';

	// Bottom border
	canvas[y + 2][x] = '+';
	for (int i = 1; i < box_width - 1; i++)
		canvas[y + 2][x + i] = '-';
	canvas[y + 2][x + box_width - 1] = '+';
}

// 2) Dessiner en positionnant avec layout calculé
void draw_ast_at(t_ast *node, char canvas[MAX_HEIGHT][MAX_WIDTH], int x, int y, t_layout layout)
{
	if (!node)
		return;

	char label[64] = {0};
	if (node->type == PIPE)
		snprintf(label, sizeof(label), "PIPE");
	else if (node->type == AND)
		snprintf(label, sizeof(label), "&&");
	else if (node->type == OR)
		snprintf(label, sizeof(label), "||");
	else if (node->type == CMD)
	{
		if (node->command.args && node->command.args[0])
			snprintf(label, sizeof(label), "%s", node->command.args[0]);
		else
			snprintf(label, sizeof(label), "CMD");

		for (int i = 1; node->command.args && node->command.args[i]; i++) {
			strncat(label, " ", sizeof(label) - strlen(label) - 1);
			strncat(label, node->command.args[i], sizeof(label) - strlen(label) - 1);
		}
	}
	else
		snprintf(label, sizeof(label), "NODE");

	int label_len = strlen(label);
	int box_width = label_len + 4;

	if (node->type == PIPE || node->type == AND || node->type == OR)
	{
		t_layout left_layout = calc_layout(node->pipe.left);
		t_layout right_layout = calc_layout(node->pipe.right);
		int spacing = 6;

		// Position enfants
		int left_x = x - layout.width/2 + left_layout.center_x;
		int right_x = left_x + left_layout.width + spacing;

		// Dessiner enfants
		draw_ast_at(node->pipe.left, canvas, left_x, y + 6, left_layout);
		draw_ast_at(node->pipe.right, canvas, right_x, y + 6, right_layout);

		// Dessiner parent
		place_node(canvas, x - box_width/2, y, label);

		// Dessiner connexions verticales
		int vert_start_y = y + 3;
		canvas[vert_start_y][x] = '|';

		int vert_end_y = y + 5;
		canvas[vert_end_y][left_x] = '|';
		canvas[vert_end_y][right_x] = '|';

		// Ligne horizontale entre branches enfants
		for (int i = left_x + 1; i < right_x; i++)
			canvas[vert_end_y][i] = '-';

		// Branches diagonales
		if (vert_end_y - vert_start_y > 1)
		{
			int mid_y = (vert_start_y + vert_end_y) / 2;
			canvas[mid_y][x - 1] = '/';
			canvas[mid_y][x + 1] = '\\';
		}
		else
		{
			canvas[vert_start_y + 1][x - 1] = '/';
			canvas[vert_start_y + 1][x + 1] = '\\';
		}
	}
	else
	{
		// Feuille simple
		place_node(canvas, x - box_width / 2, y, label);
	}
}

void print_canvas(char canvas[MAX_HEIGHT][MAX_WIDTH])
{
	for (int i = 0; i < MAX_HEIGHT; i++)
	{
		int j = MAX_WIDTH - 1;
		while (j > 0 && (canvas[i][j] == ' ' || canvas[i][j] == 0))
			j--;
		canvas[i][j + 1] = '\0';
		if (j > 0)
			printf("%s\n", canvas[i]);
	}
}

void print_ast_graphical(t_ast *root)
{
	char canvas[MAX_HEIGHT][MAX_WIDTH];

	printf("+-----------------------+\n");
	printf("|          AST	        |\n");
	printf("+-----------------------+\n");

	if (!root)
		return;
	for (int i = 0; i < MAX_HEIGHT; i++)
		for (int j = 0; j < MAX_WIDTH; j++)
			canvas[i][j] = ' ';

	// Calculer layout
	t_layout layout = calc_layout(root);

	// Dessiner à partir de x = layout.center_x + marge (ex: 2)
	draw_ast_at(root, canvas, layout.center_x + 2, 0, layout);

	print_canvas(canvas);
}

