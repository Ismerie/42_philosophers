# 42_philosophers

42_philosophers est un projet de l'école 42 concu autour du célèbre problème des philosophes de la table d'Edsger Dijkstra qui permet d'aborder la **communication inter-processus**.  
Pour la partie obligatoire une solution doit être trouvée en utilisant uniquement **les threads et les mutex**.  
Pour la partie bonus il faut utiliser **les processus et des sémaphores**.

### 💡 Concept
Les philosophes sont assis autour d'une table, avec une grande assiette de spaghetti en son centre. Ils ont chacun une fourchette, mais il leur faut 2 fourchettes pour manger, ils doivent donc emprunter la fourchette de leur voisin pour manger. Ce-dernier ne peut pas utiliser sa fourchette quand elle est empruntée.  
Au bout d'un certain temps sans manger les philosophes meurent de faim. Le but de l'exercice est donc de créer un **algorithme qui maintient en vie les philosophes autant que possible**.

## 📋 Règles

* Les spaghettis ne peuvent être mangés qu'avec 2 fourchettes
* Il y a autant de fourchettes que de philosophes
* Chaque philosophe mange, dort et réfléchit successivement
* Si un philosophe n'a pas mangé pendant un certain temps il mourra de faim
* Les philosophes ne peuvent pas communiquer entre eux
  

  
Le programme doit prendre plusieurs paramètres :

* **```number_of_philosophers```**: le nombre de philosophes autour de la table.
* **```time_to_die```**: un nombre representant le temps en millisecondes qu'un philosophe peut vivre après un repas. Si un philosophe n'a pas commencé à manger ```time_to_die``` millisecondes après le début de son dernier repas ou le début de la simulation, il mourra.
* **```time_to_eat```**: un nombre représentant le temps en millisecondes qu'un philosophe met pour terminer son repas. Pendant ce temps-là, le philosophe garde ses deux fourchettes en main.
* **```time_to_sleep```**:  le temps en millisecondes qu'un philosophe passe à dormir.
* **```number_of_times_each_philosopher_must_eat```**: un argument optionnel qui permet au programme de s'arrêter si tous les philosophes ont mangé au moins autant de fois. Si cet argument n’est pas précisé, la simulation continue jusqu’à la mort d’un philosophe.

Le programme génère un message chaque fois qu'un philosophe entreprend une action, formaté de cette façon :

```
[timestamp_in_ms] [X] has taken a fork
[timestamp_in_ms] [X] is eating
[timestamp_in_ms] [X] is sleeping
[timestamp_in_ms] [X] is thinking
[timestamp_in_ms] [X] died
```

## Partie Obligatoire - Threads et Mutex
Dans la partie obligatoire, **chaque philosophe est un thread** et **chaque fourchette est protégée par un mutex**. Il y a exactement une fourchette entre chaque philosophe et un philosophe doit prendre les fourchettes à sa gauche et à sa droite immédiate pour manger.

### 🛠️ Usage
Allez dans le dossier ```philo``` et utilisez la commande ```make``` pour compiler puis exécutez avec : 
```
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philo_must_eat]
```
Les arguments doivent être des entiers compris entre 0 et INT_MAX représentant une durée en millisecondes. Par exemple :
```
/philo 4 800 200 200 5
```

## Partie Bonus - Processus et Sémaphores
Pour la partie bonus de ce projet, la problématique est la même à quelques différences près : **les philosophes sont désormais des processus** et **les fourhcettes sont désormais un sémaphore de comptage**. Les fourchettes sont disposées au centre de la table lorsqu'elles ne sont pas utilisées et n'importe quel philosophe peut prendre n'importe quelle fourchette.

### 🛠️ Usage
Allez dans le dossier ```philo_bonus``` et utilisez la commande ```make``` pour compiler puis exécutez avec : 
```
./philo_bonus <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philo_must_eat]
```
Comme la partie obligatoire, les arguments doivent être des entiers compris entre 0 et INT_MAX représentant un temps en millisecondes. Par exemple :
```
/philo_bonus 4 800 200 200 5
```

***
