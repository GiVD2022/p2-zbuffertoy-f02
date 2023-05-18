#include "Animation.hh"

void Animable::addAnimation(shared_ptr<Animation> anim) {
    QTextStream(stdout) << "animation added" <<"\n";
    animFrames.push_back(anim);
}

void Animable::update(int nframe) {
    qDebug()<<"animation updated";
    bool trobat = false;
    int i;
    for (i = 0; i<animFrames[animFrames.size()-1]->frameFinal && !trobat; i++)
        trobat = animFrames[i]->frameFinal>=nframe;

    aplicaTG(animFrames[i-1]->transf);
}
