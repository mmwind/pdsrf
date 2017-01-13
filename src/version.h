/*
 * version.h
 *
 *  Created on: 23 нояб. 2015 г.
 *      Author: lladmin
 */

/**
 *
 * \page Detailed changelog page
 *
 * \section one_sec 20.20.2015
 * Отлажен класс DecisionStump +
 *
 * Добавлен Verbose метод для класса BaseClassifier +
 *
 * Добавлен BaseClassifier.getInfo() +
 *
 * DecisionStump.predict(Dataset d)
 *
 * Attribute тип добавлен, но не закончен. Пока остаётся висеть.
 *
 *
 * --------------------------------
 *\section two_sec 21.20.2015
 *
 * Базовый класс генератор сплит-кандидатов BaseSplitCandidateGenerator
 *
 * Абстракция для поддержки различных типов разбиений. Пока остаётся висеть.
 *
 * Внедрён базовый класс Base для всех объектов
 *
 * Добавлено базовое исключение для всех объектов проекта
 *
 * SampleSplitCandidateGenerator интегрировани в Decision stump
 *
 * Базовый класс Base выставлен родительским для всех соответствующих классов
 *
 * Возможность цитирования \cite louppe2014understanding добавлена. Для этого требуется latex и perl в PATH
 *
 * --------------------------------
 *\section two_sec 22.20.2015
 *
 *Todolist страница добалена
 *
 * --------------------------------
 *\section three_sec 23.20.2015
 *
 * Добавлен класс BasePreprocessor, Randomizer, etc
 * Переработана архитектура проекта
 *
 * --------------------------------
 *
 *\section four_sec 26.20.2015
 *
 * CSV file support added in draft(debug required)
 *
 * Pattern class AbstractFactory added
 *
 * Factory pattern used to produce unified interface to file readers.
 *
 * EIGEN error assertion macro redefined to produce exception
 *
 *
 *\section five_sec 27.20.2015
 *
 * Оказалось, что EIGEN error assertion macro выскакивает и в не ошибочных ситуациях. Поэтому пока оставим это без изменений.
 * CSV Reader закончен
 *
 *\section six_sec 28.20.2015
 *
 * Добавлены классы BaseTreeNode, BaseTree
 *
 * Исправлен Randomizer из RandomSplitGenerator
 *
 * BaseSplitCandidateGenerator.getSubsetBySplit для разделения на подмножества по выбраному сгенерированному сплиту
 *
 * Теперь сплиты будут работать маскируя сэмплы
 *
 *\section seven_sec 29.20.2015
 *
 * BaseSplitCandidateGenerator.getSubsetBySplit перенесён в BaseTree.
 *
 * Добавлена рекурсивная процедура обучения дерева learn
 *
 *
 *\section seven_sec 30.20.2015
 *
 * Реализован экспорт дерева в R скрипт для partykit
 *
 * --------------------------------
 *\section todo_sec TODOlist
 *
 * Генеартор сплит-кандидатов создаёт массив каждый раз при следующем ветвлении, но это можно делать один раз, а потом просто отсеивать сплиты вне текущей ячейки.
 *
 *
 *--------------------------------
 *
 */

#ifndef VERSION_H_
#define VERSION_H_
/**
 * @page Code convention
 *
 *
 */





#endif /* VERSION_H_ */
