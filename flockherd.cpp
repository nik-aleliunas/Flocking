#include "flockherd.h"
#include <sys/time.h>

FlockHerd::FlockHerd(size_t m_NumFlocks) : mFlocks()
{
    mFlocks.reserve(m_NumFlocks);
    srand(time(0));
    resize(m_NumFlocks);
    follow_rule = false;
}

void FlockHerd::draw()
{
    for(int i = 0; i < mFlocks.size(); ++i)
    {
        mFlocks[i].draw();
    }
}

void FlockHerd::rules(float m_Dt)
{
    int flashed = 0;
    for(int i = 0; i < mFlocks.size(); ++i)
    {
        mFlocks[i].leaderFollowing(i, mFlocks[0]);
        mFlocks[i].cohesion(i, mFlocks);
        mFlocks[i].alignment(i, mFlocks);
        mFlocks[i].seperation(i, mFlocks);
        mFlocks[i].interpolateFlash(m_Dt);
        mFlocks[i].interpolateStimulus(i, mFlocks);
        mFlocks[i].predatoryAction(i, mFlocks, m_Dt);
    }
}

void FlockHerd::seek(QVector3D m_TargetPosition)
{
    for(int i = 0; i < mFlocks.size(); ++i)
    {
        mFlocks[i].seek(m_TargetPosition);
    }
}

void FlockHerd::animate(float m_Dt)
{
    for(int i = 0; i < mFlocks.size(); ++i)
    {
        mFlocks[i].animate(m_Dt, follow_rule);
        for(int j = 0; j < mFlocks.size(); ++j)
        {
            if(i != j)
                mFlocks[i].collide(mFlocks[j], follow_rule);
        }
    }
}

void FlockHerd::resize(int m_NumFlocks)
{
    if(m_NumFlocks < mFlocks.size())
    {
        mFlocks.resize(m_NumFlocks);
    }
    else if(m_NumFlocks > mFlocks.size())
    {
        int difference = m_NumFlocks - mFlocks.size();
        for(int i = 0; i < difference; ++i)
        {
            QVector3D position(((float)rand()/RAND_MAX - 0.5f) * 100.0f,
                               ((float)rand()/RAND_MAX - 0.5f) * 100.0f,
                               0);//((float)rand()/RAND_MAX - 0.5f) * 100.0f);
            QVector3D velocity(((float)rand()/RAND_MAX - 0.5f) * 100.0f,
                               ((float)rand()/RAND_MAX - 0.5f) * 100.0f,
                               0);//((float)rand()/RAND_MAX - 0.5f) * 100.0f);

            float sightRadius = 10;
            float sightAngle = 5;
            float CohesionWeight = 3.5;
            float SeperationWeight = 1.5;
            float AlignmentWeight = 2.5;
            float PredatorWeight = 20;
            float followWeight = 10;
            float maxSpeed = 20;
            float maxTurn = 0.1;
            float theta_phase = (float)(rand() % 1000)*PI/500; //starting phase
            float frequency = 13.0;// + (float)((rand() - (RAND_MAX/2)) % 1000)/1000;
            float resetting_strength = 4;// + (float)((rand() - (RAND_MAX/2)) % 1000)/10000;
            Flock newFlock(position, velocity, CohesionWeight, SeperationWeight, AlignmentWeight, PredatorWeight, followWeight,
                           sightRadius, maxSpeed, maxTurn, sightAngle, theta_phase, frequency, resetting_strength);

            mFlocks.push_back(newFlock);
        }

    }
}
void FlockHerd::setLeader()
{
    follow_rule = !follow_rule;
    mFlocks[0].setLeaderColor(follow_rule);
}
