/*
* 免责声明：
* 本软件是开源程序，您可以自由使用、修改和发布它，使用 GNU 通用公共许可证版本 2（GPLv2）的条款。
* 请注意，在根据GPLv2发布本软件之前，您必须遵守以下条款：
* 1. 任何修改和派生作品必须同样采用GPLv2，并在您的派生作品中提供GPLv2的完整文本。
* 2. 您必须保留原始代码的版权通告，并在您的项目中明确指明原始作者和软件的来源。
* 3. 如果您分发本软件，您必须提供完整的源代码，以满足GPLv2的要求。这包括您的修改和派生作品的源代码。
* 4. 本软件是按"原样"提供的，不附带任何明示或暗示的保证。作者对于使用本软件造成的任何直接、间接、偶发、特殊、典型或惩戒性损害不承担责任。
* 使用此代码即表示您同意遵守GPLv2的所有要求和免责声明的条件。
* 请仔细阅读GNU通用公共许可证版本2以了解更多详细信息。您可以在 http ://www.gnu.org/licenses/gpl-2.0.html 上找到GPLv2的完整文本。
* [作者姓名]: bilibili：随风而息
* [地址]:https://github.com/AMXZzzz/SF_TRT_62.git
* [日期]: 2023/10/26
*/
#include "Actuator.h"

#define MAX_SIZE 1024						//! 共享内存大小
#define MapFileName "sf_61_shared_memory"   //! 共享内存ID

//! 初始化共享内存
bool initmem(SharedMemory** sharedmemory) {
	HANDLE MapFile = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, MAX_SIZE, MapFileName);
	if (MapFile == NULL) {
		return false;
	}

	*sharedmemory = (SharedMemory*)MapViewOfFile(MapFile, FILE_MAP_ALL_ACCESS, 0, 0, MAX_SIZE);
	if (*sharedmemory == NULL) {
		return false;
	}
	
	return true;
}

//! 拟放在obs插件中
void test() {
	//! 初始化共享内存
	SharedMemory* sharedmemory;
	if (!initmem(&sharedmemory)) return;  //! 一定要在UI端初始化共享内存，否则退出

	//! 创建执行器
	Actuator ac(sharedmemory);

#if 1 
	//! 共享内存测试: 
	//! 共享内存创建时，值是不定值，如signal->ai_start_signal 可能是false,也可能是true
	//! 需要给定初始值，尝试：ui端已经初始化共享内存，则跳过初始化
	sharedmemory->s_info.yolo_tyoe = 0;											//! yolo类型
	sharedmemory->s_info.frame_type = 1;										//! 推理框架
	sharedmemory->s_info.equipment = 0;											//! 设备
	sharedmemory->s_info.lock_type = 0;											//! 自瞄对象方式
	sharedmemory->s_info.mousec_type = 2;										//! 使用sendinput
	sharedmemory->s_info.control_model = 0;										//! 使用的控制算法
	sharedmemory->s_info.model_path = "cf_yolov5s_15w_640_2label.onnx";			//! 模型路径
	sharedmemory->s_info.logger_path = "";										//! 日志存放路径

	sharedmemory->s_signal.dll_exit_signal = false;								//! dll 退出信号
	sharedmemory->s_signal.ai_start_signal = true;								//! 执行器开始信号
	sharedmemory->s_signal.show_detect_window = true;							//! 显示检测窗口信号
	sharedmemory->s_signal.category_filter = true;								//! 类别筛选
	sharedmemory->s_signal.first_class = true;									//! 第一类别
	sharedmemory->s_signal.second_class = false;								//! 第二类别
	sharedmemory->s_signal.third_class = false;									//! 第三类别
	sharedmemory->s_signal.fourth_class = false;								//! 第四类别
	sharedmemory->s_signal.auto_trigger = false;									//! 自动扳机
	sharedmemory->s_signal.keep_move = false;									//! 持续移动

	sharedmemory->s_data.conf = 0.3;							//! 置信度指针
	sharedmemory->s_data.iou = 0.1;								//! iou置信度指针
	sharedmemory->s_data.aim_position = 0.7;					//! 瞄准位置
	sharedmemory->s_data.aim_range = 640;						//! 自瞄范围,以屏幕中间为中心的 aim_range * aim_range正方形
	sharedmemory->s_data.aim_key = 0x02;						//! 自瞄触发键
	sharedmemory->s_data.aim_key2 = 0x02;						//! 自瞄触发键2
	sharedmemory->s_data.aim_key3 = 0x02;						//! 自瞄触发键3
	sharedmemory->s_data.auto_model = 1;						//! 扳机方式
	sharedmemory->s_data.auto_key = 0x02;						//! 扳机按键 key
	sharedmemory->s_data.auto_key2 = 0x02;						//! 扳机按键 key2
	sharedmemory->s_data.auto_key3 = 0x02;						//! 扳机按键 key3
	sharedmemory->s_data.auto_trigger_x_scale = 1.0;			//! 自动扳机左右触发范围比例
	sharedmemory->s_data.auto_trigger_up_scale = 1.0;			//! 自动扳机上部触发范围比例
	sharedmemory->s_data.auto_trigger_down_scale = 1.0;			//! 自动扳机下部触发范围比例
	sharedmemory->s_data.kp_x = 0.3;
	sharedmemory->s_data.ki_x = 0.1;
	sharedmemory->s_data.kd_x = 0.1;
	sharedmemory->s_data.kp_y = 0.3;
	sharedmemory->s_data.ki_y = 0.1;
	sharedmemory->s_data.kd_y = 0.1;
	sharedmemory->s_data.max_pixel = 15;						//! 最大移动像素
	sharedmemory->s_data.delay_base = 150;						//! 基础延时
	sharedmemory->s_data.delay_delay = 60;						//! 随机延时
#endif

	//! 监听循环
	while (true) {
		//! 启动AI线程信号
		if (sharedmemory->s_signal.ai_start_signal == true) {
			sharedmemory->s_signal.ai_start_signal = false;	//! 复位信号，不然一直在创建线程
			ac.start();	//! 启动AI
		}

		//! 监听到退出dll信号
		if (sharedmemory->s_signal.dll_exit_signal == true) {
			//! 复位信号
			sharedmemory->s_signal.dll_exit_signal = false;

			ac.exit();		//! 使执行器线程退出
			ac.join();		//! 等待执行器退出

			//! 卸载自身dll，如果有
		}

		//! 手动退出
		if (GetAsyncKeyState(0x23)) {
			sharedmemory->s_signal.dll_exit_signal = true;
		}
		//! 手动启动
		if (GetAsyncKeyState(0x24)) {
			sharedmemory->s_signal.ai_start_signal = true;
		}
	}
}

//! 测试

int main() {
	test();

	return 0;
}
//! 笔记
//! - 找出内存泄露，并解决
//! - 范围判定存在bug，放弃使用相对距离进行判断，使用屏幕中心做计算
//! - 尝试使用头文件分布声明共享内存
//! - 考虑优化yolo基类，以便增加非yolo系的框架（如预处理的归一化，模型的检查(增加States状态)，后处理）
//! - 考虑增加推理扩展模块（类obs的插件注册），防止依赖臃肿