// GOAP_.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "Action.h"
#include "Solver.h"
#include "GameState.h"

#include <iostream>
#include <vector>

using namespace goap;
int main()
{
    std::cout << "Wargame Goap  running...\n";
    std::vector<Action> actions;

    const int hasWeapon = 10;
    const int hasAmmo = 15;
    const int reload = 20;
    const int playerInRange = 30;
    const int hasEnoughHealth = 35;
    const int attackPlayer = 40;

    Action move("searchPlayer", 5);
    move.setPrecondition(playerInRange, false);
    move.setEffect(playerInRange, true);
    actions.push_back(move);

    Action Reload("Reloading", 1);
    Reload.setPrecondition(reload, false);
    Reload.setPrecondition(hasWeapon, true);
    Reload.setEffect(reload, true);
    actions.push_back(Reload);

    Action EndReload("Reloading", 3);
    EndReload.setPrecondition(hasAmmo, false);
    EndReload.setEffect(hasAmmo, true);
    actions.push_back(EndReload);

    Action getWeapon("find weapon", 3);
    getWeapon.setPrecondition(hasWeapon, false);
    getWeapon.setEffect(hasWeapon, true);
    actions.push_back(getWeapon);

    Action healing("gain heal",4);
    healing.setPrecondition(hasEnoughHealth, false);
    healing.setEffect(hasEnoughHealth, true);
    actions.push_back(healing);

    Action health("more 50%", 5);
    health.setPrecondition(hasEnoughHealth, true);
    health.setPrecondition(hasAmmo, true);
    health.setPrecondition(hasWeapon, true);
    health.setPrecondition(playerInRange, true);
    health.setEffect(attackPlayer, true);
    actions.push_back(health);

    Action shoot("shoot the player", 5);
    shoot.setPrecondition(attackPlayer, false);
    shoot.setPrecondition(hasEnoughHealth, true);
    shoot.setPrecondition(hasAmmo, true);
    shoot.setPrecondition(hasWeapon, true);
    shoot.setPrecondition(playerInRange, true);
    shoot.setEffect(attackPlayer, true);
    actions.push_back(shoot);



    GameState initial_state;
    initial_state.setVariable(reload, false);
    initial_state.setVariable(hasAmmo, false);
    initial_state.setVariable(hasWeapon, false);
    initial_state.setVariable(playerInRange, false);
    initial_state.setVariable(hasEnoughHealth, false);

    GameState final_state;
    final_state.setVariable(attackPlayer, true);
    final_state.priority_ = 50;

    Planner as;
    try {
        std::vector<Action> the_plan = as.plan(initial_state, final_state, actions);
        std::cout << "Found a path!\n";
        for (std::vector<Action>::reverse_iterator rit = the_plan.rbegin(); rit != the_plan.rend(); ++rit) {
            std::cout << rit->name() << std::endl;
        }
    }
    catch (const std::exception&) {
        std::cout << "Sorry, could not find a path!\n";
    }
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
