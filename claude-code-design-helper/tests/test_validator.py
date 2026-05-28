"""Tests for the DesignValidator class."""

import pytest
from claude_code_design_helper.validator import DesignValidator
from claude_code_design_helper.designer import DesignSuggestion


class TestDesignValidator:
    def setup_method(self):
        self.validator = DesignValidator()

    def test_valid_suggestion(self):
        suggestion = DesignSuggestion(
            title="API Design",
            description="RESTful API with proper error handling and rate limiting.",
            priority=3,
            tags=["python", "api"],
        )
        issues = self.validator.validate(suggestion)
        assert issues == []
        assert self.validator.is_valid(suggestion) is True

    def test_empty_title(self):
        suggestion = DesignSuggestion(
            title="",
            description="A valid description here for testing purposes.",
            priority=1,
            tags=["test"],
        )
        issues = self.validator.validate(suggestion)
        assert "Title cannot be empty." in issues

    def test_short_description(self):
        suggestion = DesignSuggestion(
            title="Short",
            description="Short",
            priority=1,
            tags=["test"],
        )
        issues = self.validator.validate(suggestion)
        assert any("Description too short" in issue for issue in issues)

    def test_invalid_priority(self):
        suggestion = DesignSuggestion(
            title="Bad Priority",
            description="A valid description that is long enough for the test.",
            priority=10,
            tags=["test"],
        )
        issues = self.validator.validate(suggestion)
        assert any("Priority" in issue for issue in issues)

    def test_no_tags(self):
        suggestion = DesignSuggestion(
            title="No Tags",
            description="A valid description that is long enough for the test case.",
            priority=2,
            tags=[],
        )
        issues = self.validator.validate(suggestion)
        assert "At least one tag is required." in issues