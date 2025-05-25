#include "minishell.h"
#include <string.h>

#define MAX_WIDTH 200
#define MAX_HEIGHT 50

void place_node(char canvas[MAX_HEIGHT][MAX_WIDTH], int x, int y, const char *label)
{
    int i = 0;
    while (label[i] && x + i < MAX_WIDTH - 1)
    {
        canvas[y][x + i] = label[i];
        i++;
    }
}

void draw_ast(t_ast *node, char canvas[MAX_HEIGHT][MAX_WIDTH], int x, int y, int spacing)
{
    if (!node || y >= MAX_HEIGHT)
        return;

    char label[64];

    if (node->type == PIPE)
        snprintf(label, sizeof(label), "PIPE");
    else if (node->type == COMMAND)
    {
        snprintf(label, sizeof(label), "%s", node->command.args[0] ? node->command.args[0] : "CMD");
        for (int i = 1; node->command.args && node->command.args[i]; i++)
        {
            strncat(label, " ", sizeof(label) - ft_strlen(label) - 1);
            strncat(label, node->command.args[i], sizeof(label) - ft_strlen(label) - 1);
        }
    }

    place_node(canvas, x, y, label);

    if (node->type == PIPE)
    {
        // Draw branches with offsets
        draw_ast(node->pipe.left, canvas, x - spacing, y + 2, spacing / 2);
        draw_ast(node->pipe.right, canvas, x + spacing, y + 2, spacing / 2);

        // draw connection lines (optional)
        if (y + 1 < MAX_HEIGHT && x - spacing + 2 > 0 && x + spacing - 2 < MAX_WIDTH)
        {
            canvas[y + 1][x - spacing / 2] = '/';
            canvas[y + 1][x + spacing / 2] = '\\';
        }
    }
}

void print_canvas(char canvas[MAX_HEIGHT][MAX_WIDTH])
{
    for (int i = 0; i < MAX_HEIGHT; i++)
    {
        int j = MAX_WIDTH - 1;
        while (j > 0 && canvas[i][j] == ' ')
            j--;
        canvas[i][j + 1] = '\0'; // trim end
        if (j > 0)
            printf("%s\n", canvas[i]);
    }
}

void print_ast_graphical(t_ast *root)
{

	ft_printf("+-----------------------+\n");
	ft_printf("|  AST                 |\n");
	ft_printf("+-----------------------+\n");

    char canvas[MAX_HEIGHT][MAX_WIDTH];

    // Initialize canvas
    for (int i = 0; i < MAX_HEIGHT; i++)
        for (int j = 0; j < MAX_WIDTH; j++)
            canvas[i][j] = ' ';

    draw_ast(root, canvas, MAX_WIDTH / 2, 0, MAX_WIDTH / 4); // x=center, y=0, spacing=large
    print_canvas(canvas);
}
