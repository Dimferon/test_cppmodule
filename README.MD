## Пример проекта С++ подключаемого модуля (AuroraSdk)

Обязательно обратите внимание на версии подключаемых модулей, а именно:
- в test_cppmodule\test_cppmodule.cpp
- в test_cppmodule\qmldir
- в test_cppmodule\plugin.qmltypes (это генерируемый утилитой qmlplugindump файл, ручками его делать гиблое дело)
- в файлах где будет идти подключение плагина -> 'import test_module.test_cppmodule *0.1*'

Пример подключения плагина к проекту https://github.com/Dimferon/AuroraSdkModuleExample
Документация по созданию моделей в Qt: https://doc.qt.io/qt-5/qtqml-modules-qmldir.html#writing-a-qmltypes-file
