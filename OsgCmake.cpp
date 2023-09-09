#include <iostream>
#include <filesystem>
#include <string>
#include <cstdlib>
#include <fstream>

namespace fs = std::filesystem;

int main() {
    // 第一步
    fs::path current_path = fs::current_path();
    fs::path third_party_x64_path = current_path / "3rdParty_x64";
    fs::path x64_path = third_party_x64_path / "x64";
    fs::path third_party_path = current_path / "3rdParty";
    fs::rename(x64_path, third_party_path);
    fs::remove_all(third_party_x64_path);

    fs::path osg_old_path = current_path / "OpenSceneGraph-OpenSceneGraph-3.6.5";
    fs::path osg_new_path = current_path / "OpenSceneGraph";
    fs::rename(osg_old_path, osg_new_path);

    // 第二步
    fs::path build_path = osg_new_path / "build";
    fs::create_directory(build_path);

    std::string cmake_command = "cmake -S " + osg_new_path.string() + " -B " + build_path.string() +
        " -G \"Visual Studio 17 2022\" -A x64" +
        " -DACTUAL_3RDPARTY_DIR=" + third_party_path.string() +
        " -DBUILD_OSG_EXAMPLES=ON" +
        " -DCMAKE_INSTALL_PREFIX=" + osg_new_path.string() +
        " -DBUILD_MFC_EXAMPLE=ON";

    int result_configure = system(cmake_command.c_str());

    // 在桌面上创建zyh.txt文件并写入内容
    std::string desktop_path = std::getenv("USERPROFILE");
    desktop_path += "\\Desktop\\zyh.txt";

    std::ofstream file(desktop_path);

    if (result_configure == 0) {
        file << "没有红色提示" << std::endl;
        std::cout << "配置成功" << std::endl;
        file << "Generate成功" << std::endl;
        std::cout << "生成成功" << std::endl;
    }
    else {
        file << "有红色提示" << std::endl;
        std::cout << "配置失败" << std::endl;
        file << "Generate失败" << std::endl;
        std::cout << "生成失败" << std::endl;
    }

    file.close();
}
