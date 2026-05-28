from setuptools import setup, find_packages

setup(
    name="claude-code-design-helper",
    version="0.1.0",
    description="AI-powered code design assistant for Claude Code projects",
    author="Claude Code Design Team",
    packages=find_packages(),
    install_requires=[
        "click>=8.0.0",
        "rich>=12.0.0",
    ],
    entry_points={
        "console_scripts": [
            "ccdh=claude_code_design_helper.cli:main",
        ],
    },
    python_requires=">=3.8",
)