#include <memory>
#include <QString>
#include "mainwindow.h"
#include "list.h"

class TDequeController {
 public:
  explicit TDequeController(TMainWindow* view);

  void PushFirstDequeFront(const QString& name);
  void PushSecondDequeFront(const QString& name);

  void PushFirstDequeBack(const QString& name);
  void PushSecondDequeBack(const QString& name);

  void PopFirstDequeFront();
  void PopSecondDequeFront();

  void PopFirstDequeBack();
  void PopSecondDequeBack();

  void CompareDeques();

 protected:
  TMainWindow* View;
  TBiDirectionalList<QString> FirstDeque;
  TBiDirectionalList<QString> SecondDeque;
};