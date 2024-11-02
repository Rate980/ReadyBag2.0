#include "main-screen.h"
#include "screen.h"
#include "index.h"

namespace main_screen
{
    int selectionIndex = 0;
    const int selectionsMax = 2;
    MainSelection selections[selectionsMax + 1] = {MainSelection::Bell, MainSelection::Setting, MainSelection::Add};
}

ScreenState mainLoop(M5GFX *display, Reader *reader, Encoder *encoder, m5::Button_Class button, bool isScan, std::vector<uint16_t> *registeredIds)
{
    using namespace main_screen;

    auto state = MainState::NotScan;
    auto nextScreenState = ScreenState::Main;
    if (isScan)
    {
        state = MainState::Nomal;
        auto existIds = reader->read();
        for (auto registeredId : *registeredIds)
        {
            bool isExist = false;
            for (auto existId : existIds)
            {
                if (registeredId == existId)
                {
                    isExist = true;
                    break;
                }
            }

            if (!isExist)
            {
                state = MainState::Alert;
                break;
            }
        }
    }

    if (button.wasPressed())
    {
        auto currentSelection = selections[selectionIndex];
        switch (currentSelection)
        {
        case MainSelection::Bell:
            nextScreenState = ScreenState::Main;
            break;
        case MainSelection::Setting:
            nextScreenState = ScreenState::Setting;
            break;
        case MainSelection::Add:
            nextScreenState = ScreenState::Add;
            break;
        default:
            break;
        }
    }

    selectionIndex = updaterIndex(selectionIndex, selectionsMax, encoder->difference());
    drawMainScreen(SPIFFS, display, state, selections[selectionIndex]);
    return nextScreenState;
}
