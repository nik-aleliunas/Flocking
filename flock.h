#ifndef FLOCK_H
#define FLOCK_H

#include <QVector3D>
#include <math.h>
#include <QVector>

#define PI 3.14159265
#define FLASH_DRAW_FRAMES 5

/**
 * @brief The Flock class
 * it deals with the flock behavior
 */
class Flock
{
public:

    /**
     * @brief Flock
     * the constructor
     */
    Flock(QVector3D m_Position = QVector3D(), QVector3D m_Velocity = QVector3D(),
          float CohesionWeight = 10.0f, float SeperationWeight = 0.01, float AlignmentWeight = 1, float PredatorWeight = 1, float FollowWeight = 1.5,
          float m_SightDistance = 1.0f, float maxSpeed = 0.8, float mMaxTurnRadius = 0.5, float maxAngle = PI,
          float n_theta_phase = 0, float n_frequency = 13, float n_resetting_strength = 1);

    /**
     * @brief draws the flock
     */
    void draw();

    /**
     * @brief updateVelocity based on the target position given. this only changes the velocity
     * @param m_TargetPosition
     */
    QVector3D seek(QVector3D m_TargetPosition);
    QVector3D arrival(QVector3D m_TargetPosition);
    QVector3D wander();

    /**
     * @brief animates the flock, i.e. it changes the actual position.
     * @param m_Dt the time difference
     */
    void animate(float m_Dt, bool follow_rule);

    /**
     * @brief collides the given flock with another one. it changes position of the current one only
     * @param m_Other the other flock
     */
    void collide(Flock & m_Other, bool follow_rule);
    /**
     * @brief moves flock towards center of all visible flocks.
     * @param i position in vector of this flock
     *        mFlocks the flock vector.
     */
    void cohesion(int i, QVector<Flock>  mFlocks);
    void seperation(int i, QVector<Flock>  mFlocks);
    void alignment(int i, QVector<Flock>  mFlocks);
    void predatoryAction(int i, QVector<Flock> mFlocks, float m_Dt);
    void leaderFollowing(int i, Flock & m_Leader);
    void interpolateFlash(float m_Dt);
    void interpolateStimulus(int i, QVector<Flock>  mFlocks);
    float get_theta_phase();
    void setLeaderColor(bool follow_rule);
protected:
    bool inSightRange(Flock & m_Other);
    float dotProduct(QVector3D a, QVector3D b);
    QVector3D crossProduct(QVector3D a, QVector3D b);

private:

    QVector3D   mPosition;  /**< the current position of the flock. */
    QVector3D   mVelocity;  /**< the veolocity of the flock. */
    QVector3D   mColor;     /**< the color of the flock. */
    QVector3D   mCohesionVector;
    QVector3D   mSeperationVector;
    QVector3D   mAlignmentVector;
    QVector3D   mPredatorVector;
    QVector3D   mFollowVector;
    float       mCohesionWeight;
    float       mSeperationWeight;
    float       mAlignmentWeight;
    float       mPredatorWeight;
    float       mFollowWeight;
    float       mMaxSpeed;
    float       mMaxTurnRadius;
    float       mSightDistance; /**< the distance the flock can see. */
    float       mSightAngle;
    double      theta_phase;
    float       stimulus;
    float       frequency;
    float       resetting_strength;
    int         flashed;
    bool        predator;
};

#endif // FLOCK_H
