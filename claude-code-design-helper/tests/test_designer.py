"""Tests for the ProjectDesigner class."""

import pytest
from claude_code_design_helper.designer import ProjectDesigner, DesignSuggestion


class TestProjectDesigner:
    def test_initialization(self):
        designer = ProjectDesigner("test-project", "python")
        assert designer.project_name == "test-project"
        assert designer.language == "python"
        assert designer.suggestions == []

    def test_analyze_requirements(self):
        designer = ProjectDesigner("myapp", "python")
        reqs = ["User authentication", "Database integration"]
        suggestions = designer.analyze_requirements(reqs)

        assert len(suggestions) == 2
        assert suggestions[0].title == "Requirement 1"
        assert suggestions[0].description == "User authentication"
        assert suggestions[0].priority == 1
        assert "python" in suggestions[0].tags

    def test_get_top_suggestions(self):
        designer = ProjectDesigner("test", "python")
        designer.analyze_requirements(["A", "BB", "CCC", "DDDD", "EEEEE"])
        top = designer.get_top_suggestions(n=3)

        assert len(top) == 3
        assert top[0].priority >= top[1].priority >= top[2].priority

    def test_empty_requirements(self):
        designer = ProjectDesigner("empty", "python")
        suggestions = designer.analyze_requirements([])
        assert suggestions == []
        assert designer.get_top_suggestions() == []