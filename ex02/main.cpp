#include "PmergeMeVec.hpp"
#include "PmergeMeList.hpp"
#include <algorithm>
#include <sys/time.h>

static long long getCurrentTimeMicros() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return static_cast<long long>(ts.tv_sec) * 1000000 + ts.tv_nsec / 1000;
}

static void	printBefore(char **argv)
{
	std::cout << "Before : " << std::endl;
	for(unsigned int i = 1; argv[i] != NULL; i++)
		std::cout << argv[i] << " ";
	std::cout << std::endl;
}

template <typename T>
static void	printAfter(T conteneur)
{
	std::cout << "After : " << std::endl;
	for(unsigned int i = 0; i < conteneur.size(); i++)
		std::cout << conteneur[i] << " ";
	std::cout << std::endl;
}

// template <typename T>
// static void	is_sort(T conteneur)
// {
// 	if (std::is_sorted(conteneur.begin(), conteneur.end()) == true)
// 		std::cout << "Sort" << std::endl;
// 	else
// 		std::cout << "Not Sort" << std::endl;
// }

int main(int argc, char **argv)
{
	if (argc >= 2)
	{
		try
		{
			long long start_time = getCurrentTimeMicros();
			PmergeMeVec sortVec(argv);
			long long end_time = getCurrentTimeMicros();
			printBefore(argv);
			printAfter(sortVec.getArray());
			std::cout << "Avec std::vector<int> temps d'execution : " << end_time - start_time << " microseconde" << std::endl;
			// is_sort(sortVec.getArray());
			start_time = getCurrentTimeMicros();
			PmergeMeList sortList(argv);
			end_time = getCurrentTimeMicros();
			std::deque<int> list = sortList.getList();
			std::cout << "Avec std::deque<int> temps d'execution : " << end_time - start_time << " microseconde" << std::endl;
			// is_sort(sortList.getList());
		}
		catch(std::exception const& e)
		{
			std::cout << e.what() << std::endl;
			return (1);
		}
	}
	else
	{
		std::cout << "Invalid nbr arg" << std::endl;
		return (1);
	}
	return (0);
}

// Petits tableaux :

//     std::deque peut être plus efficace pour des opérations fréquentes d'insertion et de suppression en début et en fin de tableau par rapport à std::vector. C'est parce que std::deque alloue généralement des blocs de mémoire contigus plus petits, ce qui peut conduire à une meilleure localité spatiale.
//     std::vector peut nécessiter des allocations mémoire et des déplacements plus fréquents lors de l'ajout ou de la suppression d'éléments, car il alloue une mémoire contiguë qui doit être agrandie ou réduite lors de ces opérations.
//     exemple : std::vector si on ajoute plus que la taille initiale qu'il faisait puissance de 2 va reallouer tout un tableau et copier tout ce qu'il y'avait dans l'ancien cela prend beaucoup de temps

// Grands tableaux :

//     Pour des tableaux plus grands, la performance de std::vector et std::deque peut devenir similaire, voire en faveur de std::vector dans certains cas. Cela est dû au fait que std::vector a tendance à avoir une meilleure localité temporelle, car tous les éléments sont stockés de manière contiguë en mémoire.
//     std::deque pourrait introduire plus de surtêtes (overheads) liées à la gestion de la mémoire pour les blocs plus petits, ce qui peut affecter les performances lors de l'accès à des éléments distants.

//Vector : acces rapide au element mais operation d'insertion et suppr lente car il faut deplacer tout  les elements
//Deque : acces rapide au debut et a la fin et tres bonne insertion des element car lis mais acces sequentiel aux elements plus longue que pour un vector
