## Пример проекта С++ подключаемого модуля для AuroraOs

Обязательно обратите внимание на версии подключаемых модулей, а именно:
- в test_cppmodule\test_cppmodule.cpp
- в test_cppmodule\qmldir
- в test_cppmodule\plugin.qmltypes (это генерируемый утилитой qmlplugindump файл, ручками его делать гиблое дело)
- в файлах где будет идти подключение плагина -> 'import test_module.test_cppmodule *0.1*'