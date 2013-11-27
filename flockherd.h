#ifndef FLOCKHERD_H
#define FLOCKHERD_H

#include "flock.h"
#include <QVector>

/**
 * @brief The FlockHerd class
 */
class FlockHerd
{
public:

    /**
     * @brief FlockHerd
     * param m_NumFlocks the number of flocks
     */
    FlockHerd(size_t m_NumFlocks);

    /**
     * @brief draws the flock
     */
    void draw();

    /**
     * @brief updateVelocity based on the target position given. this only changes the velocity
     * @param m_TargetPosition
     */
    void seek(QVector3D m_TargetPosition);

    /**
     * @brief animates the flock, i.e. it changes the actual position.
     * @param m_Dt the time difference
     */
    void animate(float m_Dt);

    /**
     * @brief resizes the number of flocks in the system
     * @param m_NumFlocks
     */
    void resize(int m_NumFlocks);
    /**
     *@brief interpolates flocking rules
     *
     */
    void rules(float m_Dt);
    void setLeader();

private:

    QVector<Flock>  mFlocks;        /**< the vector holding all the flocks. */
    bool follow_rule;
};

#endif // FLOCKHERD_H
