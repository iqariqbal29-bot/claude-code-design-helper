"""Core design generation logic for Claude Code projects."""

from dataclasses import dataclass, field
from typing import List, Optional


@dataclass
class DesignSuggestion:
    """Represents a single design suggestion from the AI."""
    title: str
    description: str
    priority: int = 1
    tags: List[str] = field(default_factory=list)

    def summary(self) -> str:
        return f"[P{self.priority}] {self.title}: {self.description[:50]}..."


class ProjectDesigner:
    """Generates design suggestions for a given project context."""

    def __init__(self, project_name: str, language: str = "python"):
        self.project_name = project_name
        self.language = language
        self.suggestions: List[DesignSuggestion] = []

    def analyze_requirements(self, requirements: List[str]) -> List[DesignSuggestion]:
        """Analyze raw requirements and produce design suggestions."""
        for i, req in enumerate(requirements):
            suggestion = DesignSuggestion(
                title=f"Requirement {i+1}",
                description=req,
                priority=min(i + 1, 5),
                tags=[self.language, "requirement"],
            )
            self.suggestions.append(suggestion)
        return self.suggestions

    def get_top_suggestions(self, n: int = 3) -> List[DesignSuggestion]:
        """Return the top N suggestions by priority."""
        sorted_suggestions = sorted(
            self.suggestions, key=lambda s: s.priority, reverse=True
        )
        return sorted_suggestions[:n]