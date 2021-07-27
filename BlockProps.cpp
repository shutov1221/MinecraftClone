#include "BlockProps.h"

namespace {
    struct AttributeBlockFile
    {
        static std::string Id;
        static std::string TexTop;
        static std::string TexBottom;
        static std::string TexSide;
        static std::string TexAll;
        static std::string Type;
        static std::string Solid;
    };
    std::string AttributeBlockFile::TexTop = "TexTop";
    std::string AttributeBlockFile::TexBottom = "TexBottom";
    std::string AttributeBlockFile::TexSide = "TexSide";
    std::string AttributeBlockFile::TexAll = "TexAll";
    std::string AttributeBlockFile::Solid = "Solid";
};

BlockProps::BlockProps(const std::string block) {
    std::ifstream stream("res/blocks/" + block + ".dcblock");
    int atlasSize = 16;

    float xSize = 1.0f / 16.0f;
    float ySize = 1.0f / 16.0f;

    if (!stream.is_open()) {
        std::cout << "Unable to open file!" << block.c_str() << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string line;
    while (getline(stream, line))
    {
        std::stringstream ss;

        if (line.find(AttributeBlockFile::TexTop + ":") == 0) {
            int x, y;
            line.replace(0, AttributeBlockFile::TexTop.size() + 1, "");
            ss << line;
            ss >> y >> x;

            float indexX = ((float)x) / atlasSize;
            float indexY = ((float)y) / atlasSize;

            blockTex.top =
            {
                glm::vec2(indexX,         indexY + ySize),
                glm::vec2(indexX + xSize, indexY + ySize),
                glm::vec2(indexX + xSize, indexY),
                glm::vec2(indexX,         indexY),
            };

        }
        else if (line.find(AttributeBlockFile::TexSide + ":") == 0) {
            int x, y;
            line.replace(0, AttributeBlockFile::TexSide.size() + 1, "");
            ss << line;
            ss >> y >> x;

            float indexX = ((float)x) / atlasSize;
            float indexY = ((float)y) / atlasSize;

            blockTex.front = blockTex.back =
            {
                glm::vec2(indexX,         indexY + ySize),
                glm::vec2(indexX + xSize, indexY + ySize),
                glm::vec2(indexX + xSize, indexY),
                glm::vec2(indexX,         indexY),
            };

            blockTex.right =
            {
                glm::vec2(indexX + xSize, indexY + ySize),
                glm::vec2(indexX,         indexY + ySize),
                glm::vec2(indexX,         indexY),
                glm::vec2(indexX + xSize, indexY),
            };

            blockTex.left =
            {
                glm::vec2(indexX,         indexY + ySize),
                glm::vec2(indexX + xSize, indexY + ySize),
                glm::vec2(indexX + xSize, indexY),
                glm::vec2(indexX,         indexY),
            };

        }
        else if (line.find(AttributeBlockFile::TexBottom + ":") == 0) {
            int x, y;
            line.replace(0, AttributeBlockFile::TexBottom.size() + 1, "");
            ss << line;
            ss >> y >> x;

            float indexX = ((float)x) / atlasSize;
            float indexY = ((float)y) / atlasSize;

            blockTex.bottom =
            {
                glm::vec2(indexX,         indexY + ySize),
                glm::vec2(indexX + xSize, indexY + ySize),
                glm::vec2(indexX + xSize, indexY),
                glm::vec2(indexX,         indexY),
            };

        }
        else if (line.find(AttributeBlockFile::TexTop + ":") == 0) {
            int x, y;
            line.replace(0, AttributeBlockFile::TexTop.size() + 1, "");
            ss << line;
            ss >> y >> x;

            float indexX = ((float)x) / atlasSize;
            float indexY = ((float)y) / atlasSize;

            blockTex.top =
            {
                glm::vec2(indexX,         indexY),
                glm::vec2(indexX + xSize, indexY),
                glm::vec2(indexX + xSize, indexY + ySize),
                glm::vec2(indexX,         indexY + ySize),
            };
        }
        else if (line.find(AttributeBlockFile::TexAll + ":") == 0) {
            int x, y;
            line.replace(0, AttributeBlockFile::TexAll.size() + 1, "");
            ss << line;
            ss >> y >> x;

            float indexX = ((float)x) / atlasSize;
            float indexY = ((float)y) / atlasSize;

            blockTex.top = blockTex.bottom = blockTex.left = blockTex.right = blockTex.front = blockTex.back =
            {
                glm::vec2(indexX,         indexY),
                glm::vec2(indexX + xSize, indexY),
                glm::vec2(indexX + xSize, indexY + ySize),
                glm::vec2(indexX,         indexY + ySize),
            };
        }
        else if (line.find(AttributeBlockFile::Solid + ":") == 0) {
            bool solid;
            line.replace(0, AttributeBlockFile::TexSide.size(), "");
            ss << line;
            ss >> solid;

            this->solid = solid;
        }
    }
}