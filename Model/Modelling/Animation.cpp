#include "Animation.hh"

void Animable::addAnimation(shared_ptr<Animation> anim) {
    animFrames.push_back(anim);
}

void Animable::update(int nframe) {
    if (animFrames.empty()) {
        qDebug() << "No animations found.";
        return;
    }
    bool trobat = false;
    int i;
    for (i = 0; i<animFrames[animFrames.size()-1]->frameFinal && !trobat; i++)
        trobat = animFrames[i]->frameFinal>=nframe;

    aplicaTG(animFrames[i-1]->transf);
}
