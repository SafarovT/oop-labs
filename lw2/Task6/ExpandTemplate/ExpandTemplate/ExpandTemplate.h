#pragma once
#include <string>
#include <unordered_map>

using TemplateParams = std::unordered_map<std::string, std::string>;

std::string ExpandTemplate(std::string const& tpl, TemplateParams const& params);