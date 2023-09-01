# Philosophers - 42 School Project

## 📋 Résumé

Qui aurait cru que philosopher serait si mortel? Ce projet est une introduction aux threads et aux processus en C. On y apprend à manipuler des threads, découvrir les mutex et la mémoire partagée.

## 💻 Technologies Utilisées

- Langage: C
- Threading: Pthreads (pour la partie obligatoire)
- Synchronisation: Mutex

## 📦 Installation

```bash
git clone https://github.com/Jeanmichel7/Philosophers.git
cd Philosophers
make
```

## 📜 Règles du projet

- Écrit en C selon la norme 42.
- Pas de fuites mémoire.
- Utilisation de `make` pour la compilation.
- Pas de variables globales.
- Le programme prend plusieurs arguments pour configurer la simulation.

## 🛠️ Utilisation

Pour exécuter le projet, utilisez la commande suivante:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
./philo 4 410 200 200
```

### Logs

Les logs du programme suivent ce format:

- `timestamp_in_ms X has taken a fork`
- `timestamp_in_ms X is eating`
- `timestamp_in_ms X is sleeping`
- `timestamp_in_ms X is thinking`
- `timestamp_in_ms X died`

## 🖼️ Galerie

![image](https://raw.githubusercontent.com/Jeanmichel7/philosopher/image/screenshot.png)
