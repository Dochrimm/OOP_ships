#include "AbilityResponce.h"

AbilityResponce::AbilityResponce()
{
    double_damage_status = DoubleDamageStatus::disable;
};
void AbilityResponce::doubleDamageActivated()
{
    double_damage_status = DoubleDamageStatus::activated;
};
void AbilityResponce::disableDoubleDamage()
{
    double_damage_status = DoubleDamageStatus::disable;
};
void AbilityResponce::scannerReturnTrue()
{
    scanner_status = ScannerStatus::detected;
};
void AbilityResponce::scannerReturnFalse()
{
    scanner_status = ScannerStatus::clear;
};
void AbilityResponce::setLastAbility(AbilityResponce::Ability ability)
{
    last_ability_used = ability;
};
AbilityResponce::DoubleDamageStatus AbilityResponce::getDoubleDamageStatus() const
{
    return double_damage_status;
};
void AbilityResponce::getAbilityResult() const
{
    switch (last_ability_used)
    {
    case AbilityResponce::Ability::DoubleDamage:
    {
        std::cout << "Dublul atac activated"<< "\n";
        break;
    }
    case AbilityResponce::Ability::Scanner:
    {
        if (scanner_status == ScannerStatus::detected) {
            std::cout << "Navy on radar!"<< "\n";
        } else {
            std::cout << "Side is clear"<< "\n";
        };
        break;
    }
    case AbilityResponce::Ability::Bombardment:
    {
        std::cout << "Successful bombardment"<< "\n";
        break;
    }
    default:
    {
        break;
    };
    };
};
