#include "flock.h"
#include <OpenGL/gl.h>
#include <cmath>
#include <glu.h>
#define PREDATOR_MODIFIER 2

Flock::Flock(QVector3D m_Position, QVector3D m_Velocity,
             float CohesionWeight/* = 10.0f*/, float SeperationWeight, float AlignmentWeight, float PredatorWeight, float FollowWeight,
             float m_SightDistance, float maxSpeed, float maxTurn, float sightAngle, float n_theta_phase, float n_frequency, float n_resetting_strength) :
             mPosition(m_Position), mVelocity(m_Velocity), mColor(),
             mCohesionWeight(CohesionWeight), mSeperationWeight(SeperationWeight), mAlignmentWeight(AlignmentWeight),
             mPredatorWeight(PredatorWeight), mFollowWeight(FollowWeight),
             mSightDistance(m_SightDistance), mMaxSpeed(maxSpeed), mMaxTurnRadius(maxTurn), mSightAngle(sightAngle),
             theta_phase(n_theta_phase), frequency(n_frequency), resetting_strength(n_resetting_strength)
{
    stimulus = 0;
    flashed = 0;
    if(rand() % 100 > 90) {
        //predators are red
        predator = true;
        mMaxSpeed /=PREDATOR_MODIFIER;
        mMaxTurnRadius *= PREDATOR_MODIFIER;
        mColor.setX(1);
        mColor.setY((float)(rand() % 1000)/3000 + 0.2); //g
        mColor.setZ((float)(rand() % 1000)/3000 + 0.2);
    } else {
        predator = false;
        mColor.setX((float)(rand() % 1000)/3000 + 0.7); //r (0.7 to 1)
        mColor.setY((float)(rand() % 1000)/3000 + 0.7); //g
        mColor.setZ((float)(rand() % 1000)/3000 + 0.7);
    }
    mVelocity.normalize();
    mVelocity *=mMaxSpeed;
}

void Flock::draw()
{
    glColor3f(mColor.x(), mColor.y(), mColor.z());

    glPushMatrix();
    glTranslatef(mPosition.x(), mPosition.y(), mPosition.z());
    QVector3D axis = crossProduct(QVector3D(0,1,0), mVelocity);
    float theta = acos(dotProduct(QVector3D(0,1.0,0), mVelocity)/mVelocity.length())*180/PI;
    glRotatef(theta, axis.x(), axis.y(), axis.z());

    //bottom
    glColor3f(mColor.x()*.5, mColor.y()*.5, mColor.z()*.5);
    glBegin(GL_TRIANGLES);
    glVertex3f(0,2,0);
    glVertex3f(1,-2,0);
    glVertex3f(-1,-2,0);
    glEnd();
    //left side
    glColor3f(mColor.x()*.6, mColor.y()*.5, mColor.z()*.5);
    glBegin(GL_TRIANGLES);
    glVertex3f(0,2,0);
    glVertex3f(1,-2,0);
    glVertex3f(0,-2,1);
    glEnd();
    //right side
    glColor3f(mColor.x()*.5, mColor.y()*.6, mColor.z()*.5);
    glBegin(GL_TRIANGLES);
    glVertex3f(0,2,0);
    glVertex3f(-1,-2,0);
    glVertex3f(0,-2,1);
    //back
    glEnd();
    glColor3f(mColor.x()*.5, mColor.y()*.4, mColor.z()*.5);
    glBegin(GL_TRIANGLES);
    glVertex3f(0,-2,1);
    glVertex3f(1,-2,0);
    glVertex3f(-1,-2,0);
    glEnd();

    GLUquadricObj* sphereGlu;
    if (flashed > 0) {
        glColor3f(mColor.x(), mColor.y(), mColor.z());
        flashed--;
    } else
        glColor3f(0,0,0);
    sphereGlu = gluNewQuadric();
    //glPushMatrix();
    glTranslatef(0,-2, 0);
    gluSphere(sphereGlu, .5, 20, 25);

    glPopMatrix();


}
void Flock::cohesion(int i, QVector<Flock> mFlocks)
{
    float count = 0;
    QVector3D averagePosition;
    mCohesionVector = QVector3D(0,0,0);
    for(int j = 0; j < mFlocks.size(); j++)
    {
        if(j != i && mFlocks[j].predator == predator)
        {
            if(inSightRange(mFlocks[j])) {
                count++;
                averagePosition += mFlocks[j].mPosition;
            }
        }
    }
    if (count > 0)
    {
        averagePosition /= count;
        mCohesionVector = seek(averagePosition);
    }
}
void Flock::seperation(int i, QVector<Flock> mFlocks)
{
    QVector3D averageDirection;
    QVector3D temp;
    float length = 0;
    mSeperationVector = QVector3D(0,0,0);
    for(int j = 0; j < mFlocks.size(); j++)
    {
        if(j != i && mFlocks[j].predator == predator)
        {
            if(inSightRange(mFlocks[j])) {
                //least amount of force on the ones farthest away.
                temp = (mPosition - mFlocks[j].mPosition);
                length = temp.length();
                temp.normalize();
                temp /= length;
                averageDirection += temp;
            }
        }
    }
    mSeperationVector = averageDirection;
}
void Flock::alignment(int i, QVector<Flock>  mFlocks)
{
    float count = 0;
    QVector3D averageDirection;

    mAlignmentVector = QVector3D(0,0,0);
    for(int j = 0; j < mFlocks.size(); j++)
    {
        if(j != i && mFlocks[j].predator == predator)
        {
            if(inSightRange(mFlocks[j])) {
                count++;
                averageDirection += (mFlocks[j].mVelocity).normalized();
            }
        }
    }
    if(count > 0)
    {
        averageDirection /= count;
        mAlignmentVector = averageDirection;
    }
}
void Flock::predatoryAction(int i, QVector<Flock> mFlocks, float m_Dt)
{
    int closest = i;
    float count = 0;
    mPredatorVector = QVector3D(0,0,0);
    if(predator) {
        for(int j = 0; j < mFlocks.size(); j++) {
            if(j != i && mFlocks[j].predator != predator && inSightRange(mFlocks[j])) {
                if(closest == i) {
                    closest = j;
                } else if((mPosition - mFlocks[closest].mPosition).length() < (mPosition - mFlocks[j].mPosition).length()) {
                    closest = j;
                }
            }
        }
        if (closest != i)
            mPredatorVector = arrival(mFlocks[closest].mPosition + mFlocks[closest].mVelocity*m_Dt);
    } else {
        QVector3D averagePosition;
        for(int j = 0; j < mFlocks.size(); j++)
        {
            if(j != i && mFlocks[j].predator != predator && inSightRange(mFlocks[j]))
            {
                count++;
                averagePosition += mFlocks[j].mPosition;
            }
        }
        if (count > 0)
        {
            averagePosition /= count;
            mPredatorVector = -seek(averagePosition);
        }
    }
}
void Flock::leaderFollowing(int i, Flock &m_Leader)
{
    mFollowVector = QVector3D(0,0,0);
    if(i == 0) {
        mFollowVector = wander();
    } else {
        if(inSightRange(m_Leader))
        {
            mFollowVector = arrival(m_Leader.mPosition - m_Leader.mVelocity*0.01);
        }
    }
}

QVector3D Flock::seek(QVector3D m_TargetPosition)
{
    QVector3D target_vector = (m_TargetPosition - mPosition);
    if(target_vector.length() > mMaxSpeed)
    {
        target_vector.normalize();
        target_vector *= mMaxSpeed;
    }
    QVector3D steering_vector = target_vector - mVelocity;
    steering_vector.normalize();
    steering_vector *=mMaxTurnRadius;
    return steering_vector;
}
QVector3D Flock::arrival(QVector3D m_TargetPosition)
{
    QVector3D target = seek(m_TargetPosition);
    if((mPosition - m_TargetPosition).length() < 1)
        target *= (mPosition - m_TargetPosition).length();
    return target;
}
//Not proper wander code
QVector3D Flock::wander()
{
    return seek(QVector3D(((float)rand()/RAND_MAX - 0.5f) * 100.0f,
                ((float)rand()/RAND_MAX - 0.5f) * 100.0f,
                ((float)rand()/RAND_MAX - 0.5f) * 100.0f));
}
void Flock::animate(float m_Dt, bool follow_rule)
{
    double viewport[4];
    glGetDoublev(GL_VIEWPORT, viewport);
    if(follow_rule) {
        mVelocity += mSeperationVector*mSeperationWeight + mFollowVector*mFollowWeight;
    } else {
        mVelocity += mCohesionVector*mCohesionWeight + mSeperationVector*mSeperationWeight
                  + mAlignmentVector*mAlignmentWeight + mPredatorVector*mPredatorWeight;
    }
    if(mVelocity.length() > mMaxSpeed)
    {
        mVelocity = mVelocity.normalized() *mMaxSpeed;
    }
    mPosition += mVelocity*m_Dt;
    if(mPosition.x() < -50)
    {
        mVelocity = mVelocity + QVector3D(1,0,0);
    } else if (mPosition.x() > 50)
    {
        mVelocity -= QVector3D(1,0,0);
    }

    if(mPosition.y() < -50)
    {
        mVelocity += QVector3D(0,1,0);
    } else if (mPosition.y() > 50)
    {
        mVelocity += QVector3D(0,-1,0);
    }
    if(mPosition.z() < -50)
    {
        mVelocity += QVector3D(0,0,1);
    } else if (mPosition.z() > 50)
    {
        mVelocity += QVector3D(0,0,-1);
    }
}

void Flock::collide(Flock & m_Other, bool follow_rule)
{
    QVector3D distance = (mPosition - m_Other.mPosition);
    if(distance.length() < 2) {
        if(!follow_rule) {
            if(predator != m_Other.predator) {
                if(!predator) {
                    mMaxSpeed /= PREDATOR_MODIFIER;
                    mVelocity *= PREDATOR_MODIFIER;
                    mMaxTurnRadius *= PREDATOR_MODIFIER;
                    predator = true;
                    mColor.setX(1);
                    mColor.setY((float)(rand() % 1000)/3000 + 0.2); //g
                    mColor.setZ((float)(rand() % 1000)/3000 + 0.2);
                }
                if(!m_Other.predator) {
                    m_Other.mMaxSpeed /= PREDATOR_MODIFIER;
                    m_Other.mVelocity *= PREDATOR_MODIFIER;
                    m_Other.mMaxTurnRadius *= PREDATOR_MODIFIER;
                    m_Other.predator = true;
                    m_Other.mColor.setX(1);
                    m_Other.mColor.setY((float)(rand() % 1000)/3000 + 0.2); //g
                    m_Other.mColor.setZ((float)(rand() % 1000)/3000 + 0.2);
                }
            }
        }
        mPosition = m_Other.mPosition + distance.normalized()*2;
    }
    //1. calculate the distance between this flock and the other
    //2. test if the flocks overlap
    //3. if they overlap, calculate the connecting vector
    //4. move this flock outwards along the connecting vector, so that the two flocks only touch
}

bool Flock::inSightRange(Flock &m_Other) {
    if(this->mSightDistance > fabs((this->mPosition - m_Other.mPosition).length()))
    {
        //if(this->mSightAngle > acos(dotProduct(mVelocity, m_Other.mPosition - mPosition)))
        //{
            return true;
        //}
    }
    return false;
}
void Flock::interpolateFlash(float m_Dt) {
    theta_phase += m_Dt*(frequency + resetting_strength*sin(stimulus - theta_phase));

    while(theta_phase > 2*PI) {
        theta_phase -= 2*PI;
        flashed = FLASH_DRAW_FRAMES;
        //set stimulus of the others.
    }
    while(theta_phase < 0) {
        theta_phase += 2*PI;
        flashed = FLASH_DRAW_FRAMES;
        //set stimulus of the others.
    }
}
void Flock:: interpolateStimulus(int i, QVector<Flock> mFlocks) {
    float stimulus_change = 0;
    float count = 0;
    for (int j = 0; j< mFlocks.size(); j++) {
        if (j != i) {
            count++;
            stimulus_change += mFlocks[i].theta_phase;
        }
    }
    if (count > 0)
        stimulus = stimulus_change/count;
    while(stimulus > 2*PI)
        stimulus -=2*PI;
    while(stimulus < 0)
        stimulus +=2*PI;
}

float Flock::dotProduct(QVector3D a, QVector3D b) {
    return (a.x()*b.x() + a.y()*b.y() + a.z()*b.z());
}
QVector3D Flock::crossProduct(QVector3D a, QVector3D b) {
    return QVector3D((a.y()*b.z() - a.z()*b.y()), (a.z()*b.x() - a.x()*b.z()), (a.x()*b.y() - a.y()*b.x()));
}

float Flock::get_theta_phase() {
    return theta_phase;
}

void Flock::setLeaderColor(bool follow_rule) {
    if(follow_rule){
        mColor.setX(0);
        mColor.setY(1); //g
        mColor.setZ(1);
    } else {
        if(predator) {
            mColor.setX(1);
            mColor.setY((float)(rand() % 1000)/3000 + 0.2); //g
            mColor.setZ((float)(rand() % 1000)/3000 + 0.2);
        } else {
            mColor.setX(1);
            mColor.setY((float)(rand() % 1000)/3000 + 0.7); //g
            mColor.setZ((float)(rand() % 1000)/3000 + 0.7);
        }
    }
}
