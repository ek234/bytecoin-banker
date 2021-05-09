#include <stdio.h>

#include "./color.h"

void Bblack()
{
	printf("\033[1;30m");
}

void black()
{
	printf("\033[0;30m");
}

void red()
{
	printf("\033[1;31m");
}

void green()
{
	printf("\033[1;32m");
}

void yellow()
{
	printf("\033[1;33m");
}

void blue()
{
	printf("\033[1;34m");
}

void Bcyan()
{
	printf("\033[1;36m");
}

void cyan()
{
	printf("\033[0;30m");
}

void white()
{
	printf("\033[1;37m");
}

void reset()
{
	printf("\033[0m");
}