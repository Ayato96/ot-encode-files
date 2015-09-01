##################################################################      Czêœæ z c++, OtClient Source      ##################################################################

[----------------------------------------------------------------------------------------------------]

core/resourcemanager.cpp
1. (W std::string ResourceManager::readFileContents(const std::string& fileName), nad return buffer;)
   Wklepaj to:
[----------------------------------------------------------------------------------------------------]
        // Changes by DominikMS - decode file buffer
        std::string fileType = fullPath.substr(fullPath.find_last_of(".") + 1);
        std::string file_name = fullPath.substr(fullPath.find_last_of("/") + 1);

        if(fileType == "png" || fileType == "lua" || fileType == "otps" || fileType == "otui"
            || fileType == "otfont" || (fileType == "otml" && file_name != "config.otml") || fileType == "otmod")
        {
            int key = 0;
            int keys[10] = {96, 8, 25, 18, 148, 30, 68, 205, 9, 168};

            for(size_t i = 0; i < buffer.length(); i++)
            {
                buffer[i] = (uint8_t)(buffer[i] ^ keys[key]);

                if((key++) >= 9)
                    key = 0;
            }
        }

[----------------------------------------------------------------------------------------------------]
client/spritemanager.cpp
2. pod
		m_spritesFile = g_resources.openFile(file);
   dodaj:
        m_spritesFile->setDecodeKey(5);




##################################################################      Czêœæ z programem      ##################################################################

1. Wrzuæ zawartoœæ folderu "otclient" do "data" oraz do "new data"
2. Odpal program szyfruj.exe








g++ main.cpp -lGdi32 -o szyfruj.exe