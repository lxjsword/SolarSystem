
#include <GLTools.h>
#include <GLShaderManager.h>
#include <GLFrustum.h>
#include <GLBatch.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>
#include <StopWatch.h>
#include <math.h>
#include <stdio.h>

#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif
#pragma comment(lib,"gltools.lib")
#pragma comment(lib,"freeglut_static.lib")
#define PI 3.1415926f
#define N 3656
#define NS 3656.0f
#define PRECISION 0.000001f

GLShaderManager		shaderManager;			// Shader Manager
GLMatrixStack		modelViewMatrix;		// Modelview Matrix
GLMatrixStack		projectionMatrix;		// Projection Matrix
GLFrustum			viewFrustum;			// View Frustum
GLGeometryTransform	transformPipeline;		// Geometry Transform Pipeline
GLFrame             cameraFrame;

GLTriangleBatch	sunBatch;
GLTriangleBatch earthBatch;
GLTriangleBatch moonBatch;
GLTriangleBatch waterBatch;
GLTriangleBatch jinBatch;
GLTriangleBatch huoBatch;
GLTriangleBatch muBatch;
GLTriangleBatch tuBatch;
GLTriangleBatch twBatch;
GLTriangleBatch hwBatch;
GLTriangleBatch mwBatch;
GLTriangleBatch	sphereBatch;

GLuint uiTextures[11];
GLBatch waterlineLoopBatch;
GLBatch earthlineLoopBatch;
GLBatch jinlineLoopBatch;
GLBatch huolineLoopBatch;
GLBatch mulineLoopBatch;
GLBatch tulineLoopBatch;
GLBatch twlineLoopBatch;
GLBatch hwlineLoopBatch;
GLBatch mwlineLoopBatch;

GLfloat vPoints[N][3]; 
GLBatch	pointBatch;
static GLint counter;

#define AU 15.0f//���ĵ�λ=149597887.5km
#define EARTHR 0.06378f//����뾶6378km
//̫��
#define SUNR 109*EARTHR//�뾶
#define SUNCA 7.25//������
#define SUNZT 25.38//��ת����(day)

//ˮ��
#define WATERR 0.3829*EARTHR//�뾶
#define WATERGA 7.005//������
#define WATERCA 0//������
#define WATERGT 87.97f//��ת����
#define WATERZT 59.0f//��ת����
#define WATERA 0.387*AU
#define WATERL 0.206
#define WATERB WATERA*sqrt(1-WATERL*WATERL)

//����
#define JINR 0.95*EARTHR//�뾶
#define JINGA 3.395//������
#define JINCA 177.4//������
#define JINGT 225.0f//��ת����
#define JINZT 243.0f//��ת����
#define JINA 0.723*AU
#define JINL 0.0068
#define JINB JINA*sqrt(1-JINL*JINL)

//����
#define EARTHGA 0//������
#define EARTHCA 23.44//������
#define EARTHGT 365.24f//��ת����
#define EARTHZT 0.997f//��ת����
#define EARTHA 1*AU
#define EARTHL 0.0167
#define EARTHB EARTHA*sqrt(1-EARTHL*EARTHL)

//����
#define HUOR 0.532*EARTHR//�뾶
#define HUOGA 1.85//������
#define HUOCA 25.19//������
#define HUOGT 687.0f//��ת����
#define HUOZT 1.062f//��ת����
#define HUOA 1.524*AU
#define HUOL 0.0934
#define HUOB HUOA*sqrt(1-HUOL*HUOL)

//ľ��
#define MUR 11.209*EARTHR//�뾶
#define MUGA 1.303//������
#define MUCA 3.08//������
#define MUGT 4331.75f//��ת����
#define MUZT 0.41f//��ת����
#define MUA 5.203*AU
#define MUL 0.0483
#define MUB MUA*sqrt(1-MUL*MUL)

//����
#define TUR 9.458*EARTHR//�뾶
#define TUGA 2.489//������
#define TUCA 26.7//������
#define TUGT 9664.25f//��ת����
#define TUZT 0.44f//��ת����
#define TUA 9.582*AU
#define TUL 0.056
#define TUB TUA*sqrt(1-TUL*TUL)

//������
#define TWR 4*EARTHR//�뾶
#define TWGA 0.773//������
#define TWCA 97.9//������
#define TWGT 30683.81f//��ת����
#define TWZT 0.718f//��ת����
#define TWA 19.229*AU
#define TWL 0.046
#define TWB TWA*sqrt(1-TWL*TWL)

//������
#define HWR 3.883*EARTHR//�뾶
#define HWGA 1.77//������
#define HWCA 27.8//������
#define HWGT 60198.86f//��ת����
#define HWZT 0.671f//��ת����
#define HWA 30.1*AU
#define HWL 0.0097
#define HWB HWA*sqrt(1-HWL*HWL)