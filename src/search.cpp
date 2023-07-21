#include "_StateControllerExtension.h"

int findTargetStateByName(string type) {
    for (size_t i = 0; i < gStateList.size(); i++) {
        if (gStateList[i].type == type) {
            return static_cast<int>(i);
        }
    }
    return HOOK_NOT_FOUND;
}