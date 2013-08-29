#ifndef CENARIO_H
#define CENARIO_H

#define NUM_TREES 240

extern float tx1[NUM_TREES/2], tx2[NUM_TREES/2], ty1[NUM_TREES/2], ty2[NUM_TREES/2];

void drawBranches(float x, float y);

void drawTrunk(float x, float y);

void initCenario();

void cenario();


#endif /** CENARIO_H **/
