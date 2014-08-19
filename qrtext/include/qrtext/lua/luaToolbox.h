#pragma once

#include <QtCore/QSharedPointer>
#include <QtCore/QScopedPointer>

#include <qrkernel/ids.h>

#include "qrtext/core/ast/node.h"
#include "qrtext/core/error.h"
#include "qrtext/core/lexer/tokenPatterns.h"

#include "qrtext/src/lua/luaLexer.h"
#include "qrtext/src/lua/luaParser.h"

#include "qrtext/declSpec.h"

namespace qrtext {
namespace lua {

/// Facade that uses text language parsing/interpreting framework to provide services based on "QReal standard" text
/// language (Lua 5.3 subset).
///
/// Facade can be used for interpreting diagrams or for syntax analysis in generators. It allows to pass code fragments
/// as chunks (corresponding to Lua blocks) identified by Id of a node and name of the property where this code fragment
/// was taken from. It can interpret it immediately, returning result and storing syntax tree and interpreter state for
/// future uses, or can parse it and then return AST for node/property by request (note that it uses all ASTs
/// as a context for parsing next chunks).
///
/// Note that types of variables may change during parsing next chunks, so, for example, after parsing "a = 123" type
/// of "a" will be inferred as Integer, but after parsing "a = 1.0" it will be changed to Float. Generators may reliably
/// use type information only when all code in a program is parsed.
class QRTEXT_EXPORT LuaToolbox {
public:
	LuaToolbox();

	template<typename T>
	T interpret(qReal::Id const &id, QString const &propertyName, QString const &code)
	{
//		auto root = parse(id, propertyName, code);
//		return mInterpreter.interpret<T>(root, mAnalyzer);
	}

	void markAsChanged(qReal::Id const &id, QString const &propertyName);

	QSharedPointer<core::ast::Node> const &parse(qReal::Id const &id, QString const &propertyName, QString const &code);

	QSharedPointer<core::ast::Node> ast(qReal::Id const &id, QString const &propertyName) const;

//	QSharedPointer<types::TypeExpression> type(QSharedPointer<ast::Node> const &expression) const;

	QList<core::Error> const &errors() const;

private:
	QList<core::Error> mErrors;

	LuaLexer mLexer;
	LuaParser mParser;
//	SemanticAnalyzer mAnalyzer;
//	Interpreter mInterpreter;

	QHash<qReal::Id, QHash<QString, QSharedPointer<core::ast::Node>>> mAstRoots;
};

}
}
