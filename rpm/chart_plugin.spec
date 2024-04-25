Name:       test_module

Summary:    Пример подключаемого плагина с C++ кодом
Version:    1.0.0
Release:    1
License:    BSD
URL:        https://github.com/Dimferon/AuroraTestConnectModule
Source0:    %{name}-%{version}.tar.bz2
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5Gui)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(Qt5Concurrent)

%description
%{summary}.

%prep
%setup -q -n %{name}-%{version}

%build

%qmake5 

make %{?_smp_mflags}

%install
rm -rf %{buildroot}
%qmake_install

%files
%defattr(-,root,root,-)
%license LICENSE.BSD
%{_libdir}/qt5/qml/test_module/chart/*.so
%{_libdir}/qt5/qml/test_module/chart/*.qml
%{_libdir}/qt5/qml/test_module/chart/plugins.qmltypes
%{_libdir}/qt5/qml/test_module/chart/qmldir