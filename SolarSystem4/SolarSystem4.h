
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

#define AU 15.0f//天文单位=149597887.5km
#define EARTHR 0.06378f//地球半径6378km
//太阳
#define SUNR 109*EARTHR//半径
#define SUNCA 7.25//赤道倾角
#define SUNZT 25.38//自转周期(day)

//水星
#define WATERR 0.3829*EARTHR//半径
#define WATERGA 7.005//轨道倾角
#define WATERCA 0//赤道倾角
#define WATERGT 87.97f//公转周期
#define WATERZT 59.0f//自转周期
#define WATERA 0.387*AU
#define WATERL 0.206
#define WATERB WATERA*sqrt(1-WATERL*WATERL)

//金星
#define JINR 0.95*EARTHR//半径
#define JINGA 3.395//轨道倾角
#define JINCA 177.4//赤道倾角
#define JINGT 225.0f//公转周期
#define JINZT 243.0f//自转周期
#define JINA 0.723*AU
#define JINL 0.0068
#define JINB JINA*sqrt(1-JINL*JINL)

//地球
#define EARTHGA 0//轨道倾角
#define EARTHCA 23.44//赤道倾角
#define EARTHGT 365.24f//公转周期
#define EARTHZT 0.997f//自转周期
#define EARTHA 1*AU
#define EARTHL 0.0167
#define EARTHB EARTHA*sqrt(1-EARTHL*EARTHL)

//火星
#define HUOR 0.532*EARTHR//半径
#define HUOGA 1.85//轨道倾角
#define HUOCA 25.19//赤道倾角
#define HUOGT 687.0f//公转周期
#define HUOZT 1.062f//自转周期
#define HUOA 1.524*AU
#define HUOL 0.0934
#define HUOB HUOA*sqrt(1-HUOL*HUOL)

//木星
#define MUR 11.209*EARTHR//半径
#define MUGA 1.303//轨道倾角
#define MUCA 3.08//赤道倾角
#define MUGT 4331.75f//公转周期
#define MUZT 0.41f//自转周期
#define MUA 5.203*AU
#define MUL 0.0483
#define MUB MUA*sqrt(1-MUL*MUL)

//土星
#define TUR 9.458*EARTHR//半径
#define TUGA 2.489//轨道倾角
#define TUCA 26.7//赤道倾角
#define TUGT 9664.25f//公转周期
#define TUZT 0.44f//自转周期
#define TUA 9.582*AU
#define TUL 0.056
#define TUB TUA*sqrt(1-TUL*TUL)

//天王星
#define TWR 4*EARTHR//半径
#define TWGA 0.773//轨道倾角
#define TWCA 97.9//赤道倾角
#define TWGT 30683.81f//公转周期
#define TWZT 0.718f//自转周期
#define TWA 19.229*AU
#define TWL 0.046
#define TWB TWA*sqrt(1-TWL*TWL)

//海王星
#define HWR 3.883*EARTHR//半径
#define HWGA 1.77//轨道倾角
#define HWCA 27.8//赤道倾角
#define HWGT 60198.86f//公转周期
#define HWZT 0.671f//自转周期
#define HWA 30.1*AU
#define HWL 0.0097
#define HWB HWA*sqrt(1-HWL*HWL)