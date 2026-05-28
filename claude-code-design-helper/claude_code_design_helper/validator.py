"""Design validation utilities for Claude Code projects."""

from typing import List
from .designer import DesignSuggestion


class DesignValidator:
    """Validates design suggestions for consistency and completeness."""

    MIN_DESCRIPTION_LENGTH = 10
    MAX_PRIORITY = 5

    def validate(self, suggestion: DesignSuggestion) -> List[str]:
        """Validate a single design suggestion. Returns a list of issues."""
        issues: List[str] = []

        if not suggestion.title.strip():
            issues.append("Title cannot be empty.")

        if len(suggestion.description.strip()) < self.MIN_DESCRIPTION_LENGTH:
            issues.append(
                f"Description too short (min {self.MIN_DESCRIPTION_LENGTH} chars)."
            )

        if not (1 <= suggestion.priority <= self.MAX_PRIORITY):
            issues.append(f"Priority must be between 1 and {self.MAX_PRIORITY}.")

        if not suggestion.tags:
            issues.append("At least one tag is required.")

        return issues

    def is_valid(self, suggestion: DesignSuggestion) -> bool:
        """Quick check if a suggestion is valid."""
        return len(self.validate(suggestion)) == 0